-----------------------------------------------------------------------------
-- Test script
-- Scenario 4.1
-----------------------------------------------------------------------------

require("rawsend")
require("socket")

local cen = "4.1"
local suc_msg = "Scenario " .. cen .. ": ok!"
local err_msg = "Scenario " .. cen .. ": erro!"

sck = socket.bind("127.0.0.1", 8888)

assert(rawsend.setfd("socket1", sck:getfd()) == nil, err_msg)

print(suc_msg)

