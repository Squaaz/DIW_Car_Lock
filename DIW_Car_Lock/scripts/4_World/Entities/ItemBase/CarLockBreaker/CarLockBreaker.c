class DIW_Car_Lock extends ItemBase
{
		void DIW_Car_Lock()
	{

	}

	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionBreakLockVehicle);
		AddAction(ActionForceLockingVehicle);
	}
}
