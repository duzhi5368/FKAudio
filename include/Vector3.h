//-------------------------------------------------------------------
// 
//
// 
//-------------------------------------------------------------------

#pragma once

#include "Unorderly.h"

namespace Ogre
{
	namespace FKAudio
	{
		template < typename T >
		class Vector3
		{
		public:
			Vector3() : X(0), Y(0), Z(0) {};
			Vector3(T tX, T tY, T tZ) : X(tX), Y(tY), Z(tZ){};
			Vector3(const Vector3< T >& otherVector3) : X(otherVector3.X), Y(otherVector3.Y), Z(otherVector3.Z) {};

			// ============================操作符重载============================
			//-------------------------------------------------------------------
			Vector3< T > operator-() const 
			{
				return Vector3< T >(-X, -Y, -Z); 
			}
			//-------------------------------------------------------------------
			Vector3< T > operator=(const Vector3< T >& otherVector3)
			{
				X = otherVector3.X;
				Y = otherVector3.Y;
				Z = otherVector3.Z;
			}
			//-------------------------------------------------------------------
			Vector3< T > operator+(const Vector3< T >& otherVector3) const
			{
				return Vector3< T >(X + otherVector3.X, Y + otherVector3.Y, Z + otherVector3.Z);
			}
			//-------------------------------------------------------------------
			Vector3< T > operator+=(const Vector3< T >& otherVector3)
			{
				X += otherVector3.X;
				Y += otherVector3.Y;
				Z += otherVector3.Z;
				return *this;
			}
			//-------------------------------------------------------------------
			Vector3< T > operator-(const Vector3< T >& otherVector3) const
			{
				return Vector3< T >(X - otherVector3.X, Y - otherVector3.Y, Z - otherVector3.Z);
			}
			//-------------------------------------------------------------------
			Vector3< T > operator-=(const Vector3< T >& otherVector3)
			{
				X -= otherVector3.X;
				Y -= otherVector3.Y;
				Z -= otherVector3.Z;
				return *this;
			}
			//-------------------------------------------------------------------
			Vector3< T > operator*(const Vector3< T >& otherVector3) const
			{
				return Vector3< T >(X * otherVector3.X, Y * otherVector3.Y, Z * otherVector3.Z);
			}
			//-------------------------------------------------------------------
			Vector3< T > operator*=(const Vector3< T >& otherVector3)
			{
				X *= otherVector3.X;
				Y *= otherVector3.Y;
				Z *= otherVector3.Z;
				return *this;
			}
			//-------------------------------------------------------------------
			Vector3< T > operator/(const Vector3< T >& otherVector3) const
			{
				return Vector3< T >(X / otherVector3.X, Y / otherVector3.Y, Z / otherVector3.Z);
			}
			//-------------------------------------------------------------------
			Vector3< T > operator/=(const Vector3< T >& otherVector3)
			{
				X /= otherVector3.X;
				Y /= otherVector3.Y;
				Z /= otherVector3.Z;
				return *this;
			}
			//-------------------------------------------------------------------
			Vector3 < T > operator*(const T scaleNum)const 
			{
				return Vector3< T >( X * scaleNum, Y * scaleNum, Z * scaleNum);
			}
			//-------------------------------------------------------------------
			Vector3 < T > operator*=(const T scaleNum)
			{
				X *= scaleNum;
				Y *= scaleNum;
				Z *= scaleNum;
				return *this;
			}
			//-------------------------------------------------------------------
			Vector3 < T > operator/(const T scaleNum)const 
			{
				return Vector3< T >( X / scaleNum, Y / scaleNum, Z / scaleNum);
			}
			//-------------------------------------------------------------------
			Vector3 < T > operator/=(const T scaleNum)
			{
				X /= scaleNum;
				Y /= scaleNum;
				Z /= scaleNum;
				return *this;
			}
			//-------------------------------------------------------------------
			// 注意这里判断不可以是简单的 otherVector3.X == X,要考虑浮点型
			bool operator==(const Vector3< T >& otherVector3) const
			{
				return FloatEquals(X ,otherVector3.X) && FloatEquals(Y ,otherVector3.Y) && FloatEquals(Z ,otherVector3.Z);
			}
			//-------------------------------------------------------------------
			// 注意这里判断不可以是简单的 otherVector3.X == X,要考虑浮点型
			bool operator!=(const Vector3< T >& otherVector3) const
			{
				return !FloatEquals(X ,otherVector3.X) || !FloatEquals(Y ,otherVector3.Y) || !FloatEquals(Z ,otherVector3.Z);
			}
			//-------------------------------------------------------------------
			bool operator<=(const Vector3< T >& otherVector3) const
			{
				return X <= otherVector3.X && Y <= otherVector3.Y && Z <= otherVector3.Z;
			}
			//-------------------------------------------------------------------
			bool operator>=(const Vector3< T >& otherVector3) const
			{
				return X >= otherVector3.X && Y >= otherVector3.Y && Z >= otherVector3.Z;
			}
			//-------------------------------------------------------------------
			bool operator<(const Vector3< T >& otherVector3) const
			{
				return X < otherVector3.X && Y < otherVector3.Y && Z < otherVector3.Z;
			}
			//-------------------------------------------------------------------
			bool operator>(const Vector3< T >& otherVector3) const
			{
				return X > otherVector3.X && Y > otherVector3.Y && Z > otherVector3.Z;
			}
			//-------------------------------------------------------------------

			// ============================常规函数============================
			// 设置Vector3中的元素值
			void SetX( const T tX){ X = tX; }
			void SetY( const T tY){ Y = tY; }
			void SetZ( const T tZ){ Z = tZ; }
			void Set(const T tX, const T tY, const T tZ){ X = tX; Y = tY; Z = tZ; }
			void Set(const Vector3< T >&  otherVector3) { X = otherVector3.X; Y = otherVector3.Y; Z = otherVector3.Z; }
			// 获取该Vector3的长度
			T GetLength() const { return reinterpret_cast< T >(QuickSquare(X * X + Y * Y + Z * Z)); }
			// 获取该Vector3长度平方( 尽量使用这个函数,速度比GetLength()快 )
			T GetLengthSquare() const { return reinterpret_cast< T >(X * X + Y * Y + Z * Z); }
			// 两个Vector3的点乘
			T DotProduct(const Vector3< T >& otherVector3){ return (T)(X * otherVector3.X + Y * otherVector3.Y + Z * otherVector3.Z); }
			// 两个Vector3点的距离 ( 此时Vector3表示的是3D空间中点信息 )
			T GetDistance(const Vector3< T >& otherVector3) const{ return Vector3< T >(X - otherVector3.X, Y - otherVector3.Y, Z - otherVector3.Z).GetLength(); }
			// 两个Vector3点的距离的平方 ( 此时Vector3表示的是3D空间中点信息,尽量使用这个函数,速度比GetDistance()快 )
			T GetDistanceSquare(const Vector3< T >& otherVector3) const{ return (T)(X - otherVector3.X, Y - otherVector3.Y, Z - otherVector3.Z).GetLengthSquare(); }
			// 两个Vector3D的叉乘
			Vector3< T > CrossProduct(const Vector3<T>& otherVector3)const
			{ return Vector3< T >(Y * otherVector3.Z - Z * otherVector3.Y, Z * otherVector3.X - X * otherVector3.Z, X * otherVector3.Y - Y * otherVector3.X); }
			// 判断三点是否同线
			bool IsOnOneLine(const Vector3< T >& otherVector3_1, const Vector3< T >& otherVector3_2)const
			{
				T lengthSquare = (otherVector3_2 - otherVector3_1).GetLengthSquare();
				return GetDistanceSquare(otherVector3_1) < lengthSquare && GetDistanceSquare(otherVector3_2) < lengthSquare;
			}
			// 自定义阀值进行两个Vector的比较
			bool IsEquals(const Vector3< T >& otherVector3, const float tolerance = FLOAT_VALVE) const
			{
				return FloatEquals(X ,otherVector3.X, tolerance) 
					&& FloatEquals(Y ,otherVector3.Y, tolerance) 
					&& FloatEquals(Z ,otherVector3.Z, tolerance);
			}
			// 标准化向量
			Vector3< T >& Normalize()
			{
				T length = static_cast< T >(QuickSquare( reinterpret_cast<float>(X * X + Y * Y + Z * Z)));
				X *= length; Y *= length; Z *= length; 
				return *this;
			}
			// 设置Vector3的长度
			void SetLength( T newLength )
			{
				Normalize();
				*this *= newLength;
			}
			// 反转该Vector3
			void Invert(){ X *= -1.0f;  Y *= -1.0f;  Z *= -1.0f; }
			// 以一个指定的点为中心，沿Y轴旋转指定的角度
			void RotateXZBy(double dDegrees, const Vector3< T >& centerPos)
			{
				double dRad = DegToRad(dDegrees);	
				T cs = (T)cos(dRad);
				T sn = (T)sin(dRad);
				X -= center.X;
				Z -= center.Z;
				Set( X * cs - Z * sn, Y, X * sn + Z * cs);
				X += center.X;
				Z += center.Z;
			}
			// 以一个指定的点为中心，沿Z轴旋转指定的角度
			void RotateXYBy(double dDegrees, const Vector3< T >& centerPos)
			{
				double dRad = DegToRad(dDegrees);	
				T cs = (T)cos(dRad);
				T sn = (T)sin(dRad);
				X -= center.X;
				Y -= center.Y;
				Set( X * cs - Y * sn, X * sn + Y * cs, Z);
				X += center.X;
				Y += center.Y;
			}
			// 以一个指定的点为中心，沿X轴旋转指定的角度
			void RotateYZBy(double dDegrees, const Vector3< T >& centerPos)
			{
				double dRad = DegToRad(dDegrees);	
				T cs = (T)cos(dRad);
				T sn = (T)sin(dRad);
				Z -= center.Z;
				Y -= center.Y;
				Set( X, Y * cs - Z * sn, Y * sn + Z * cs);
				Z += center.Z;
				Y += center.Y;
			}
		public:
			T X;
			T Y;
			T Z;
		};
		// 定义float类型的三元向量
		typedef Vector3<float> Vector3f;
	}
}