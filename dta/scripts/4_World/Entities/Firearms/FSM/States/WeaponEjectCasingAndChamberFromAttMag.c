
class WeaponEjectCasing extends WeaponStateBase
{
	void WeaponEjectCasing (Weapon_Base w = NULL, WeaponStateBase parent = NULL) { }

	override void OnEntry (WeaponEventBase e)
	{
		super.OnEntry(e);

		wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " ejected fired out casing");
		int mi = m_weapon.GetCurrentMuzzle();
		if(m_weapon.IsChamberFiredOut(mi))
		{
			m_weapon.EjectCasing(mi);
		}
		m_weapon.SelectionBulletHide();
	}
};

class WeaponEjectCasing_W4T extends WeaponEjectCasing
{
	override bool IsWaitingForActionFinish () { return true; }
};

// eject casing and load bullet from att mag (no anim)
class WeaponEjectCasingAndChamberFromAttMag extends WeaponEjectCasing
{
	override void OnEntry (WeaponEventBase e)
	{
		super.OnEntry(e);

		int mi = m_weapon.GetCurrentMuzzle();
		pushToChamberFromAttachedMagazine(m_weapon, mi);
	}
	override void OnExit (WeaponEventBase e)
	{
		super.OnExit(e);
	}
};

class WeaponEjectCasingAndChamberFromAttMag_W4T extends WeaponEjectCasingAndChamberFromAttMag
{
	override bool IsWaitingForActionFinish () { return true; }
};

