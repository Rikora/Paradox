local class = require "include.middleclass"

-- Class name
local Example = class("Example")

function Example:initialize(message)
  self.message = message
end

function Example:printMe()
  print(self.message)
end

return Example