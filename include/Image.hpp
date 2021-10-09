#ifndef IMAGE_HPP_
#define IMAGE_HPP_


#include <iostream>
#include <vector>
#include <mutex>
#include <memory>
#include <thread>
#include <atomic>

#include "GLFW/glfw3.h"
#include "Resolution.hpp"
#include "File.hpp"
#include "Config.hpp"

class ImageLoadingScheduler;

class Image {
private:
	std::shared_ptr<GLFWimage> m_image;
	std::filesystem::path m_imagePath;
	Resolution m_resolution;
	int m_amountOfChannels;
	std::mutex m_imageMutex;
public:
	Image(std::filesystem::path t_filePath, std::shared_ptr<ImageLoadingScheduler> t_imageLoadingScheduler);
	Image(const Image&);
	Image();
	~Image();

	const size_t getSizeInBytes();
	const int 	getAmountOfChannels();

	Resolution 					getResolution();
	std::filesystem::path 		getImagePath();
	std::shared_ptr<GLFWimage> 	getGLFWImage();
	bool 						isMutexLocked();

	void load();
	void setTextureInvalid();
	
	Image& operator=(const Image&);
};
class Image;
class ImageLoadingScheduler{
    std::vector<std::pair<std::thread,std::atomic_bool>> m_threads;
    std::vector<std::shared_ptr<Image>> m_images;
    std::thread m_workerThread;
    uint16_t m_activeThreads;
	std::pair<size_t,size_t> m_tempThreadArgs;
    bool m_terminate;
    std::mutex m_schedulerMutex;

    void workLoop();
public:
	static const size_t amountOfThreads = 4;
    ImageLoadingScheduler(Config t_config);
	ImageLoadingScheduler(const ImageLoadingScheduler&);
	ImageLoadingScheduler();
    ~ImageLoadingScheduler();

	void loadImage(const size_t& t_imageIndex, const size_t& t_threadIndex);
    void addImageToSchedule(std::shared_ptr<Image> t_imagePtr);
    void destroy();

	ImageLoadingScheduler& operator=(const ImageLoadingScheduler&);
};
#endif