#include "ball.h"

Ball::Ball(int screenWidth, int screenHeight)
{
  m_screenWidth = screenWidth;
  m_screenHeight = screenHeight;
  m_x = m_screenWidth / 2.0f;
}

float Ball::GetXPos()
{
  return m_x;
}

float Ball::GetYPos()
{
  return m_y;
}

float Ball::GetSpeedX()
{
  return m_speedX;
}

float Ball::GetSpeedY()
{
  return m_speedY;
}

void Ball::Draw()
{
  DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), m_radius, WHITE);
}

void Ball::Move(float deltaTime)
{
  m_x += m_speedX * deltaTime;
  m_y += m_speedY * deltaTime;
}

void Ball::Reset(int screenWidth)
{
  m_x = screenWidth / 2.0f;
  m_y = 0;
  m_speedX = 400;
  m_speedY = 350;
}

void Ball::m_CheckYCollision()
{
  if (m_y < 0)
  {
    m_speedY *= -1;
  }
  if (m_y > m_screenHeight)
  {
    m_speedY *= -1;
  }
}

void Ball::m_CheckXCollision(int& rightPlayerPoints, int& leftPlayerPoints)
{
  if (m_x < 0)
  {
    rightPlayerPoints++;
    m_x = m_screenWidth / 2;
    m_y = 0;
    m_speedX = 300;
    m_speedY = 300;
  }

  if (m_x > m_screenWidth)
  {
    leftPlayerPoints++;
    m_x = m_screenWidth / 2;
    m_y = 0;
    m_speedX = -300;
    m_speedY = 300;
  }
}

void Ball::m_CheckBallPaddleCollision(Paddle& leftPaddle, Paddle& rightPaddle)
{
  float leftPaddleYPos = leftPaddle.GetYPos();
  float leftPaddleHeight = leftPaddle.GetHeight();
  float rightPaddleYpos = rightPaddle.GetYPos();
  float rightPaddleHeight = rightPaddle.GetHeight();

  if (CheckCollisionCircleRec(Vector2{m_x, m_y}, m_radius, leftPaddle.GetRect()))
  {
    if (m_speedX < 0)
    {
      m_speedX *= -1.1f;
      if (m_y - leftPaddleYPos > 0)
      {
        m_speedY = 250;
      }
      else
      {
        m_speedY = -250;
      }
      if (leftPaddleHeight > 10)
      {
        leftPaddle.ShrinkHeight(5);
        rightPaddle.ShrinkHeight(5);
      }
    }
  }

  if (CheckCollisionCircleRec(Vector2{m_x, m_y}, m_radius, rightPaddle.GetRect()))
  {
    if (m_speedX > 0)
    {
      m_speedX *= -1.1f;
      if (m_y - rightPaddleYpos > 0)
      {
        m_speedY = 250;
      }
      else
      {
        m_speedY = -250;
      }
      if (rightPaddleHeight > 10)
      {
        leftPaddle.ShrinkHeight(5);
        rightPaddle.ShrinkHeight(5);
      }
    }
  }
}

void Ball::CheckCollisions(Paddle& leftPaddle, Paddle& rightPaddle, int& rightPlayerPoints,
                           int& leftPlayerPoints)
{
  m_CheckYCollision();
  m_CheckXCollision(rightPlayerPoints, leftPlayerPoints);
  m_CheckBallPaddleCollision(leftPaddle, rightPaddle);
}
