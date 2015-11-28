//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#pragma once

#include <boost/smart_ptr.hpp>
#include <assert.h>
#include <algorithm>
#include <iostream>

typedef unsigned int uint32;

// 自定义断言，方便之后和Ogre结合
#ifdef _DEBUG
#define FK_ASSERT(exp) assert(exp)
#else
#define FK_ASSERT(exp) ((void)0)
#endif 

// 音效流的智能指针
typedef boost::shared_ptr<std::istream> SP_ISTREAM;

// 设置OGG音效流缓冲区大小为4KB
uint32 const	OGG_BUFFUR = 4096;
// 设置float类型比较的阀值为0.00001f
const float		FLOAT_VALVE = 0.00001f;
// 设置PI值 
const double	PI = 3.1415926535897932384626433832795028841971693993751;


namespace Ogre
{
	namespace FKAudio
	{
	//-------------------------------------------------------------------
	// 取最小值
	template < typename T > 
	inline const T& FKMin( const T& value1, const T& value2)
	{
		//return value1 < value2 ? value1, value2;
		return value1 < value2 ? value1 : value2;
	}
	//-------------------------------------------------------------------
	// 取最大值
	template < typename T > 
	inline const T& FKMax( const T& value1, const T& value2)
	{
		return value1 > value2 ? value1 : value2;
	}
	//-------------------------------------------------------------------
	// 取中间值
	template < typename T > 
	inline const T& FKClamp( const T& value1, const T& value2, const T& value3)
	{
		return FKMax(value2, FKMin(value3 , value1));
	}
	//-------------------------------------------------------------------	
	// 整合生成FourCC类型
	template <unsigned char ch0, unsigned char ch1, unsigned char ch2, unsigned char ch3>
	struct MakeFourCC
	{
		enum { value = (ch0 << 0) + (ch1 << 8) + (ch2 << 16) + (ch3 << 24) };
	};
	//-------------------------------------------------------------------
	// 判断两个float类型是否相等
	inline bool FloatEquals(const float value1, const float value2, const float tolerance = FLOAT_VALVE)
	{
		return (value1 + tolerance > value2) && (value1 - tolerance < value2);
	}
	//-------------------------------------------------------------------
	// 速求float平方根的函数
	__forceinline float QuickSquare(const float value)
	{
		__asm
		{
			movss	xmm0, value
			rsqrtss	xmm0, xmm0
			movss	value, xmm0
		}	
		return value;
	}
	//-------------------------------------------------------------------
	// 角度转弧度函数
	inline double DegToRad(double dDegrees)
	{
		return (dDegrees * (PI / 180.0));
	}
	//-------------------------------------------------------------------
	// 弧度转角度函数
	inline double RadToDeg(double dRadians)
	{
		return (dRadians * (180.0 / PI));
	}
	//-------------------------------------------------------------------
	// 自定义返回一个组结构中第一参数
	template <typename pair_type>
	struct select1st : public std::unary_function<const pair_type &,const typename pair_type::first_type &>
	{
		const typename pair_type::first_type& operator()(const pair_type& x) const
		{
			return x.first;
		}
	};
	//-------------------------------------------------------------------
	// 自定义返回一个组结构中第二参数
	template <typename pair_type>
	struct select2nd : public std::unary_function<const pair_type &,const typename pair_type::second_type &>
	{
		const typename pair_type::second_type& operator()(const pair_type& x) const
		{
			return x.second;
		}
	};
	//-------------------------------------------------------------------
	}
}
