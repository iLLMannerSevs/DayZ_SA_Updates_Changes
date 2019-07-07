class PoisoningMdfr: ModifierBase
{
	private const float 	WATER_DECREMENT_PER_SEC = -50;
	private const float 	BLOOD_DECREMENT_PER_SEC = -5;
	private const float 	POISONING_LASTS_SEC	 = 15;
	private float			m_Time;
	
	const int FOOD_POISON_AGENT_THRESHOLD_ACTIVATE = 150;
	const int FOOD_POISON_AGENT_THRESHOLD_DEACTIVATE = 50;
	
	override void Init()
	{
		m_TrackActivatedTime	= true;
		m_IsPersistent			= true;
		m_ID 					= eModifiers.MDF_POISONING;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_ACTIVE;
		
	}
	
	override bool ActivateCondition(PlayerBase player)
	{
		if(player.GetSingleAgentCount(eAgents.FOOD_POISON) > FOOD_POISON_AGENT_THRESHOLD_ACTIVATE) 
		{
			return true;
		}
		else 
		{
			return false;
		}
	}
	
	override bool DeactivateCondition(PlayerBase player)
	{
		if(player.GetSingleAgentCount(eAgents.FOOD_POISON) < FOOD_POISON_AGENT_THRESHOLD_DEACTIVATE) 
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	override void OnActivate(PlayerBase player)
	{
		player.IncreaseDiseaseCount();
	}
	
	override void OnDeactivate(PlayerBase player)
	{
		player.DecreaseDiseaseCount();
	}

	override void OnTick(PlayerBase player, float deltaT)
	{	
		/*
		player.GetStatWater().Add((WATER_DECREMENT_PER_SEC*deltaT));
		
		float currentblood = player.GetHealth("GlobalHealth", "Blood");
		player.SetHealth("GlobalHealth", "Blood", ( currentblood + (BLOOD_DECREMENT_PER_SEC*deltaT) ) );

		if ( (GetAttachedTime() / 1000) > POISONING_LASTS_SEC )
		{
			player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_POISONING);
		}
		*/
	}
};