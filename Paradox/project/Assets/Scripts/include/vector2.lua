local class = require "Scripts.include.middleclass"

-- Class name
local Vector2 = class("Vector2")

function Vector2:initialize(x, y)
   self.x = x
   self.y = y
end

function Vector2:add(other)
  return Vector2:new(self.x + other.x, self.y + other.y)
end

function Vector2:sub(other)
  return Vector2:new(self.x - other.x, self.y - other.y)
end

function Vector2:multp(other)
  return Vector2:new(self.x * other.x, self.y * other.y)
end

function Vector2:div(other)
  return Vector2:new(self.x / other.x, self.y / other.y)
end

function Vector2:copy(other)
  self.x = other.x
  self.y = other.y
end

return Vector2