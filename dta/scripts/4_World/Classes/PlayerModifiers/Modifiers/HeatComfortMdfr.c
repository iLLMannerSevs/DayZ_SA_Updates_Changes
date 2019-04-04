class HeatComfortMdfr: ModifierBase
{
	override void Init()
	{
		m_TrackActivatedTime 	= false;
		m_ID 					= eModifiers.MDF_TEMPERATURE;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_ACTIVE;
	}

	override bool ActivateCondition(PlayerBase player)
	{
		return true;
	}

	override bool DeactivateCondition(PlayerBase player)
	{
		return false;
	}

	override void OnReconnect(PlayerBase player)
	{

	}
	
	override string GetDebugText()
	{
		return m_Player.GetStatHeatComfort().Get().ToString();
	}
	
	override string GetDebugTextSimple()
	{
		return m_Player.GetStatHeatComfort().Get().ToString();
	}

	
	override void OnTick(PlayerBase player, float deltaT)
	{
		float heat_comfort = player.GetStatHeatComfort().Get();
		float health_loss;
		float value_normalized;
		
		//water loss due to high HC
		if( heat_comfort > PlayerConstants.WATER_LOSS_THRESHOLD_HC_PLUS_LOW )
		{
			value_normalized = Math.InverseLerp(PlayerConstants.WATER_LOSS_THRESHOLD_HC_PLUS_LOW, PlayerConstants.WATER_LOSS_THRESHOLD_HC_PLUS_HIGH, heat_comfort);
			value_normalized = Math.Clamp(value_normalized,0,1);
			float water_loss = deltaT * Math.Lerp(PlayerConstants.WATER_LOSS_HC_PLUS_LOW, PlayerConstants.WATER_LOSS_HC_PLUS_HIGH, value_normalized);
			player.GetStatWater().Add(-water_loss);
			//PrintString("water loss:"+water_loss.ToString());
			//-----------------------------------------
			//connected to water range
			health_loss = deltaT * Math.Lerp(PlayerConstants.HEALTH_LOSS_HC_PLUS_LOW, PlayerConstants.HEALTH_LOSS_HC_PLUS_HIGH, value_normalized);
			
		}
		if( heat_comfort < PlayerConstants.ENERGY_LOSS_THRESHOLD_HC_MINUS_LOW )
		{
			//player.SetMixedSoundState( eMixedSoundStates.FREEZING );
			value_normalized = Math.InverseLerp(PlayerConstants.ENERGY_LOSS_THRESHOLD_HC_MINUS_LOW, PlayerConstants.ENERGY_LOSS_THRESHOLD_HC_MINUS_HIGH, heat_comfort);
			value_normalized = Math.Clamp(value_normalized,0,1);
			float energy_loss = deltaT * Math.Lerp(PlayerConstants.ENERGY_LOSS_HC_MINUS_LOW, PlayerConstants.ENERGY_LOSS_HC_MINUS_HIGH, value_normalized);
			player.GetStatEnergy().Add(-energy_loss);
			//PrintString("energy loss:"+energy_loss.ToString());
			//-----------------------------------------
			//connected to energy range
			health_loss = deltaT * Math.Lerp(PlayerConstants.HEALTH_LOSS_HC_MINUS_LOW, PlayerConstants.HEALTH_LOSS_HC_MINUS_HIGH, value_normalized);
		}
		else
		{
			//player.UnsetMixedSoundState( eMixedSoundStates.FREEZING );
		}
		
		if( health_loss !=0 )
		{
			player.AddHealth("","",-health_loss);
			//PrintString("health loss:"+ health_loss.ToString());
		}
		
	}
};

