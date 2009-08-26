ANIMATION01 = 0

--The name of the template
cam01 = {}

-- ///////////////////////////////////////////////////////////////////////////////////////////////////
--Physics Actor events:
cam01["OnAnimationStarted"] = function (obj)

end

cam01["OnAnimationEnded"] = function (obj)
	anim = nil
	anim = LuaStateManager:getAnimationComponent(obj)
	
	if(anim) then

	end
end

cam01["OnAnimationUpdated"] = function (obj)

end

-- ///////////////////////////////////////////////////////////////////////////////////////////////////
-- Component Events
cam01["OnComponentCreateStart"] = function(obj)

end

cam01["OnComponentCreateFinish"] = function(obj)
	
	anim = nil
	anim = LuaStateManager:getAnimationComponent(obj)
	
	cam = nil
	cam = LuaStateManager:getCameraComponent(obj)
	
	if(anim and cam) then
		--GuiManager:setWallpaper("background.jpg")
		
		anim:setAnimationSpeed(ANIMATION01, 0.2)
		anim:playAnimation(ANIMATION01)
		
		cam:enableAnimation(true)

	end
	
end

cam01["OnStartUpdate"] = function( obj )

end

cam01["OnFinishUpdate"] = function( obj )
	
		
end

cam01["OnComponentDestroy"] = function( obj )

end

