class ActionBreakLockVehicleCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(20);
	}
};


class ActionBreakLockVehicle: ActionContinuousBase
{

  void ActionBreakLockVehicle()
	{
		m_CallbackClass = ActionBreakLockVehicleCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		//m_MessageSuccess = "";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNonRuined(1.5);
	}

	override string GetText()
	{
		return "Break car lock";
	}

  protected bool isCarDoorHood(ActionTarget target)
	{
		CarDoor carDoor = CarDoor.Cast(target.GetObject());

		CarScript car;
		if (Class.CastTo(car, target.GetParent()) && carDoor)
		{
			array<string> selections = new array<string>();
			carDoor.GetActionComponentNameList(target.GetComponentIndex(), selections);

			for (int i = 0; i < selections.Count(); i++)
			{
				string m_AnimSource = car.GetAnimSourceFromSelection(selections[i]);
				if(m_AnimSource == "DoorsHood")
					return true;
			}
		}

		return false;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(!target)
		{
			//Print("no target");
			return false;
		}

		if (!target.GetObject().IsInherited(CarDoor))
		{
			//Print("no door");
			return false;
		}


		if (isCarDoorHood(target))
		{
			//Print("no hood");
			return false;
		}


			CarScript carScript;
			if (Class.CastTo(carScript, target.GetParent()))
			{
				if (!carScript.m_Trader_Locked )
					return false;

				if (carScript.m_Trader_Locked && player.m_Trader_IsInSafezone == false)
				//Print("The Car is locked");
					return true;
			}
		//Print("NO CASE");

		return false;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		PlayerBase player = action_data.m_Player;

		action_data.m_Player.DropItem(action_data.m_MainItem);
		action_data.m_MainItem.Delete();

		CarScript carScript = CarScript.Cast(action_data.m_Target.GetParent());
		if( carScript )
		{
			carScript.m_Trader_Locked = false;
			carScript.SynchronizeValues();
		}
	}
};
