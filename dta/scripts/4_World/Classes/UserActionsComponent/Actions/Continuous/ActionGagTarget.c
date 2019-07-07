class ActionGagTarget: ActionContinuousBase
{	
	void ActionGagTarget()
	{
		m_CallbackClass = ActionCoverHeadTargetCB;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_LOW;
	}
	
	override void CreateConditionComponents()  
	{	
		
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);		
	}
		
	override string GetText()
	{
		return "#gag_person";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (item.GetQuantity() > 1)
			return false;
		
		PlayerBase targetPlayer;
		Class.CastTo(targetPlayer, target.GetObject());
		if ( !IsWearingMask(targetPlayer) ) 
		{
			if ( targetPlayer.FindAttachmentBySlotName( "Headgear" ) )
			{
				bool headgear_allows;
				headgear_allows = targetPlayer.FindAttachmentBySlotName( "Headgear" ).ConfigGetBool( "noMask" );
				if (!headgear_allows)
				{
					return false;
				}
			}
			return true;
		}
		
		return false;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{	
		PlayerBase ntarget;
		Class.CastTo(ntarget, action_data.m_Target.GetObject());
		ntarget.GetInventory().CreateInInventory("MouthRag");
		action_data.m_MainItem.TransferModifiers(ntarget);
		action_data.m_MainItem.Delete();

		action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
	}
	
	bool IsWearingMask( PlayerBase player)
	{
		if ( player.GetInventory().FindAttachment(InventorySlots.MASK) )
		{
			return true;
		}
		return false;
	}
};