
--The name of the template
katana = {}

ITEM_DEFAULT_SOUND = "../Media/Sounds/Sword hit.wav"

PARTICLE_WEAPON = "katana_particle"
PARTICLE_WEAPON_SCRIPT = "example_010"

katana["OnWeaponItemMenuStartDrag"] = function(obj)
	
end
katana["OnWeaponItemMenuFinishDrag"] = function(obj)
	
end

katana["OnWeaponInventoryActivate"] = function(obj)
	SoundManager:play(ITEM_DEFAULT_SOUND)
end

katana["OnWeaponPick"] = function(obj)
	SoundManager:play(ITEM_DEFAULT_SOUND)
	ParticleManager:stopParticle(PARTICLE_WEAPON)
end
katana["OnWeaponDrop"] = function(obj)
	SoundManager:play(ITEM_DEFAULT_SOUND)
	ParticleManager:startParticle(PARTICLE_WEAPON)
end

katana["OnComponentCreateStart"] = function(obj)
	
end

katana["OnComponentCreateFinish"] = function(obj)
	
	render = nil
	render = LuaStateManager:getRenderComponent(obj)

	weapon = nil
	weapon = LuaStateManager:getWeaponComponent(obj)
	
	if(render and weapon) then
		--ParticleManager:createParticle(RIBBON_TRAIL_PARTICLE_NAME,"example_01_A") --"example_01_A"
		
		ParticleManager:createParticle(PARTICLE_WEAPON,PARTICLE_WEAPON_SCRIPT) --"example_01_A"
		
		nodeParticle = nil
		nodeParticle = OgreManager:createChildSceneNode(render:getNode(),"katana_particle")
		

		ParticleManager:attachParticleToNode(PARTICLE_WEAPON,nodeParticle)
		ParticleManager:startParticle(PARTICLE_WEAPON)
				
		--nodeParticle:setScale(0.1,0.1,0.1)
				
		nodeTip = nil
		nodeTip = OgreManager:createChildSceneNode( render:getNode(),"katana_child_tip")
		
		trans = Vector3.ZERO
		trans = Vector3(0,0,-9)
		nodeTip:translate(trans,Node.TS_PARENT)
		
		weapon:setRibbonTrailNodeTip(nodeTip)
		
		nodeBase = nil
		nodeBase = OgreManager:createChildSceneNode( render:getNode(),"katana_child_base")
		
		weapon:setRibbonTrailNodeBase(nodeBase)
		--weapon:setRibbonTrailMaterial("swordMaterial")
		--weapon:setRibbonTrailMaterial("SwordMat")
		--weapon:setRibbonTrailMaterial("mat_trail")
		weapon:setRibbonTrailMaterial("swordMaterial")
					
			
		--initColor = ColourValue(0.1,1,0,0.1) --ColourValue.White
		--initColor = ColourValue(1,1,1,0) --ColourValue.Red
		initColor = ColourValue.Red
		weapon:setSegmentStartInitialColor(initColor)
		--endColor = ColourValue(1,1,1,0)
		endColor = ColourValue.Red 
		weapon:setSegmentEndInitialColor(endColor)
		
		--changeColor = ColourValue.Black
		--weapon:setSegmentStartColorChange(changeColor)
		--weapon:setSegmentEndColorChange(changeColor)
		
		--weapon:setRibbonTrailVisible(false)
		--weapon:setRibbonTrailWidth(18)
		
	end

	pos = Vector3.ZERO
	SoundManager:createSingleSound(SOUND_FX_REVERB, ITEM_DEFAULT_SOUND, pos, false )
	
end

katana["OnStartUpdate"] = function( obj )
	
		
end

katana["OnFinishUpdate"] = function( obj )
	
		
end

katana["OnComponentDestroy"] = function( obj )

end

