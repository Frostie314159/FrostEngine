#include "Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb/stb_image.h"
Image::Image(std::filesystem::path t_filePath, std::shared_ptr<ImageLoadingScheduler> t_imageLoadingScheduler) {
	this->m_amountOfChannels = 0;
	t_imageLoadingScheduler.get()->addImageToSchedule(std::shared_ptr<Image>(this));
}
Image::Image() {
	this->m_amountOfChannels = 0;
}
Image::Image(const Image&){

}
Image::~Image() {
	
}
const size_t Image::getSizeInBytes() {
	return static_cast<uint64_t>(this->m_resolution.width) * static_cast<uint64_t>(this->m_resolution.height) * static_cast<uint64_t>(this->m_amountOfChannels);
}
Resolution Image::getResolution() {
	return this->m_resolution;
}
const int Image::getAmountOfChannels() {
	return this->m_amountOfChannels;
}
std::filesystem::path Image::getImagePath() {
	return this->m_imagePath;
}
std::shared_ptr<GLFWimage> Image::getGLFWImage(){
	return this->m_image;
}
bool Image::isMutexLocked(){
	bool m_isLocked = this->m_imageMutex.try_lock();
	if(m_isLocked)
		this->m_imageMutex.unlock();
	return !m_isLocked;
}

void Image::load() {
	std::lock_guard<std::mutex> m_imageLockGuard(this->m_imageMutex);
	stbi_uc* m_tempPixels = stbi_load(m_imagePath.string().c_str(), &this->m_resolution.width, &this->m_resolution.height, &this->m_amountOfChannels, STBI_rgb_alpha);

	if (m_tempPixels == nullptr || stbi_failure_reason() != nullptr || this->m_resolution.getAspectRatio() != Resolution(1, 1)) {
		std::cerr << "Error loading texture" << stbi_failure_reason() << std::endl;
		this->setTextureInvalid();
		return;
	}

	this->m_image.get()->pixels = m_tempPixels;
	this->m_image.get()->height = this->m_resolution.height;
	this->m_image.get()->width = this->m_resolution.width;
}
void Image::setTextureInvalid() {
	this->m_image.get()->pixels = new stbi_uc[4*4];
	for (size_t i = 0; i < 2 * 2; i++) {
		if (i % 2 == 0) {
			this->m_image.get()->pixels[i*4] = 153;
			this->m_image.get()->pixels[i*4+1] = 0;
			this->m_image.get()->pixels[i*4+2] = 153;
			this->m_image.get()->pixels[i*4+3] = 255;
			continue;
		}
		for(size_t x=0;x<4;x++)
			this->m_image.get()->pixels[i*4+x];
	}
	this->m_resolution = Resolution(2, 2);
	this->m_amountOfChannels = 4;
}
Image& Image::operator=(const Image&){
	return *this;
}


ImageLoadingScheduler::ImageLoadingScheduler(Config t_config){
    this->m_threads = std::vector<std::pair<std::thread,std::atomic_bool>>();
    this->m_images = std::vector<std::shared_ptr<Image>>();
    this->m_workerThread = std::thread([this](){
		this->workLoop();
	});
}
ImageLoadingScheduler::ImageLoadingScheduler(const ImageLoadingScheduler&){
	
}
ImageLoadingScheduler::ImageLoadingScheduler(){

}
ImageLoadingScheduler::~ImageLoadingScheduler(){
	this->destroy();
}

void ImageLoadingScheduler::workLoop(){
    while(!this->m_terminate){
        for(size_t x=0;x<this->m_images.size();x++){
            if(!this->m_images.at(x).get()->isMutexLocked()){
                std::lock_guard<std::mutex> m_activeThreadLockGuard(this->m_schedulerMutex);
                if(this->m_activeThreads < this->m_threads.size()){
                    for(int y=0;y<this->m_threads.size();y++){
                        if(this->m_threads.at(y).second){
                            this->m_threads.at(y).first.join();
							this->m_tempThreadArgs = std::pair<size_t,size_t>{x, y};
                            this->m_threads.at(y).first = std::thread([this](){
								this->m_threads.at(this->m_tempThreadArgs.second).second = false;
    							this->m_images.at(this->m_tempThreadArgs.first).get()->load();
    							this->m_threads.at(this->m_tempThreadArgs.second).second = true;	
							});
                        }
                    }
                }
            }
        };
    }
}
void ImageLoadingScheduler::loadImage(const size_t& t_imageIndex, const size_t& t_threadIndex){
    this->m_threads.at(t_threadIndex).second = false;
    this->m_images.at(t_imageIndex).get()->load();
    this->m_threads.at(t_threadIndex).second = true;
}
ImageLoadingScheduler& ImageLoadingScheduler::operator=(const ImageLoadingScheduler&){
	return *this;
}