#include "ImageLoadingScheduler.hpp"

ImageLoadingScheduler::ImageLoadingScheduler(Config t_config){
    this->m_threads = std::vector<std::pair<std::thread,std::atomic_bool>>();
    this->m_threads.reserve(std::thread::hardware_concurrency() - std::stoi(t_config.getConfigEntry("ReservedThreads").value));
    this->m_images = std::vector<std::shared_ptr<Image>>();
    this->m_workerThread = std::thread(ImageLoadingScheduler::workLoop);
}

void ImageLoadingScheduler::workLoop(){
    while(!this->m_terminate){
        for(std::shared_ptr m_currentImage: this->m_images){
            if(!m_currentImage.get()->isMutexLocked()){
                std::lock_guard<std::mutex> m_activeThreadLockGuard(this->m_schedulerMutex);
                if(this->m_activeThreads < this->m_threads.size()){
                    for(int i=0;i<this->m_threads.size();i++){
                        if(this->m_threads.at(i).second){
                            this->m_threads.at(i).first.join();
                            this->m_threads.at(i).first = std::thread(ImageLoadingScheduler::loadImage, m_currentImage, i);
                        }
                    }
                }
            }
        };
    }

}
void ImageLoadingScheduler::loadImage(std::shared_ptr<Image> t_imagePtr, size_t t_index){
    this->m_threads.at(t_index).second = false;
    t_imagePtr.get()->load();
    this->m_threads.at(t_index).second = true;
}
void ImageLoadingScheduler::destroy(){
    this->m_terminate = true;
    for(int i=0;i<this->m_threads.size();i++)
    this->m_threads.at(i).first.join();
    }