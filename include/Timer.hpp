#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <iostream>
#include <chrono>
#include <functional>
#include <type_traits>
#include <utility>
#include <tuple>

class Timer
{
public:
	template<typename FuncType, typename... Args>
	static FuncType timeFunction(FuncType t_function(Args...),std::string t_functionName,Args&&... t_functionArgs) {
		std::chrono::high_resolution_clock::time_point m_beginTime = std::chrono::high_resolution_clock::now();

		FuncType m_return = t_function(std::forward<Args>(t_functionArgs)...);

		std::cout << t_functionName << "()... " << "took(" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_beginTime).count() << ")" << std::endl;
		return m_return;
	}
	
	template<typename... Args>
	static void timeFunction(void t_function(Args...), std::string t_functionName, Args&&... t_functionArgs) {
		std::chrono::high_resolution_clock::time_point m_beginTime = std::chrono::high_resolution_clock::now();

		t_function(std::forward<Args>(t_functionArgs)...);

		std::cout << t_functionName << "()... " << "took(" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_beginTime).count() << ")" << std::endl;
	}

	template<typename FuncType, typename... Args>
	static std::tuple<FuncType, std::chrono::milliseconds> timeFunction(FuncType t_function(Args...), Args&&... t_functionArgs) {
		std::chrono::high_resolution_clock::time_point m_beginTime = std::chrono::high_resolution_clock::now();

		FuncType m_return = t_function(std::forward<Args>(t_functionArgs)...);

		return std::tuple<FuncType, double>(m_return, std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_beginTime).count());
	}

	template<typename... Args>
	static std::chrono::milliseconds timeFunction(void t_function(Args...), Args&&... t_functionArgs) {
		std::chrono::high_resolution_clock::time_point m_beginTime = std::chrono::high_resolution_clock::now();

		t_function(std::forward<Args>(t_functionArgs)...);

		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_beginTime);
	}
	
};

#endif