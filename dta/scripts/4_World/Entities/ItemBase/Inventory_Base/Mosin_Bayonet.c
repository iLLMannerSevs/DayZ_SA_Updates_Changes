class Mosin_Bayonet extends Inventory_Base
{
	override bool CanPutAsAttachment( EntityAI parent )
	{
		if(!super.CanPutAsAttachment(parent)) {return false;}
		if ( parent.FindAttachmentBySlotName("suppressorImpro") == null && parent.FindAttachmentBySlotName("weaponMuzzleMosin") == null )
		{
			return true;
		}
		return false;
	}

	override void OnWasAttached(EntityAI parent, int slot_id)
	{
		if( parent.IsWeapon() )
		{
			parent.SetBayonetAttached(true);
		}		
	}
	
	override void OnWasDetached(EntityAI parent, int slot_id)
	{
		if( parent.IsWeapon() )
		{
			parent.SetBayonetAttached(false);
		}
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionBurnSewTarget);
		AddAction(ActionUnrestrainTarget);
		//AddAction(ActionSkinning);
		//AddAction(ActionMineBush);
		//AddAction(ActionMineTreeBark);
		AddAction(ActionBurnSewSelf);
		//AddAction(ActionShaveTarget);
		//AddAction(ActionShave);
	}
}