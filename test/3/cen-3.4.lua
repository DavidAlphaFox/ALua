-----------------------------------------------------------------------------
-- Test script
-- Scenario 3.4
-----------------------------------------------------------------------------

local cen = "3.4"
cen = "Scenario " .. cen .. ":"

require("uuid")

id = uuid.create("txt")
print(cen)
print(#id, id)
