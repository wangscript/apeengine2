State_Initialise = {}
State_Run = {}

-- ///////////////////////////////////////////////////////////////////////////////////////////////////

footstep_startTriggerFlag = false
function footstep_startTrigger(  )

	--GuiManager:setWallpaper("background.jpg")
	footstep_startTriggerFlag = true
	--enemy:setAnimationState(0)

end
-- ///////////////////////////////////////////////////////////////////////////////////////////////////

function OnStartMoving( anim )
	anim:setAnimationState(1)
end
function OnStopMoving( anim )
	anim:setAnimationState(0)
end
function OnJumped( anim )
	anim:setAnimationState(4)
end
function OnHitGround( anim )
	anim:setAnimationState(6)
end

function OnStartFalling( anim )
	anim:setAnimationState(9)
end


-- ///////////////////////////////////////////////////////////////////////////////////////////////////

State_Initialise[ "Enter" ] = function( anim )
	--GuiManager:setWallpaper("background.jpg")
      --GuiManager:setWallpaper("Play.png")
	
	anim:createLuaTriggerFunctor( "footstep_start", footstep_startTrigger )
	anim:setAnimationState(0)

	--anim:setCurrentState( State_Run )	

end

State_Initialise[ "Execute" ] = function( anim )
	--GuiManager:setWallpaper("background.jpg")

	--GuiManager:setWallpaper("background.jpg")

	

end

State_Initialise[ "Exit" ] = function( anim )

end

-- ///////////////////////////////////////////////////////////////////////////////////////////////////

State_Run[ "Enter" ] = function( anim )
	GuiManager:setWallpaper("background.jpg")
end
State_Run[ "Execute" ] = function( anim )

end
State_Run[ "Exit" ] = function( anim )

end

-- ///////////////////////////////////////////////////////////////////////////////////////////////////
-- ///////////////////////////////////////////////////////////////////////////////////////////////////
