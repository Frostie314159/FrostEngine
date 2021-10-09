#ifndef IMAGE_LOADING_SCHEDULER_HPP_
#define IMAGE_LOADING_SCHEDULER_HPP_
#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <atomic>

#include "Image.hpp"
#include "Config.hpp"

class ImageLoadingScheduler{
    std::vector<std::pair<std::thread,std::atomic_bool>> m_threads;
    std::vector<std::shared_ptr<Image>> m_images;
    std::thread m_workerThread;
    uint16_t m_activeThreads;
    bool m_terminate;
    std::mutex m_schedulerMutex;

    void loadImage(std::shared_ptr<Image> t_imagePtr, size_t t_index);
    void workLoop();
public:
    ImageLoadingScheduler(Config t_config);
    ~ImageLoadingScheduler();

    void addImageToSchedule(std::shared_ptr<Image> t_imagePtr);
    void destroy();
};
#endif