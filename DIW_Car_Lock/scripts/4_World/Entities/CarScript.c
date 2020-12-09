modded class CarScript
{
  static const string			ALARM_SOUND 				= "CLB_CarAlarm_SoundSet";
	protected ref Timer m_AlarmLoopStartTimer;
	protected EffectSound 		m_AlarmLoop;

  void PlayAlarmSound()
  {
    if (GetGame().IsClient())
		{
				if (!m_AlarmLoopStartTimer) m_AlarmLoopStartTimer = new Timer( CALL_CATEGORY_SYSTEM );
				m_AlarmLoopStartTimer.Run(0.2, this, "StartLoopSound", NULL, true);
        GetGame ().GetCallQueue (CALL_CATEGORY_SYSTEM).CallLater (this.StopSound, 30000);
		}
  }

  void StartLoopSound()
	{
		if (GetGame().IsClient())
		{
				if (m_AlarmLoop)
				{
						if ( !m_AlarmLoop.IsSoundPlaying()) PlaySoundSet( m_AlarmLoop, ALARM_SOUND, 0, 0);
				}
				else
        {
						PlaySoundSet( m_AlarmLoop, ALARM_SOUND, 0, 0);
				}
		}
	}

	void StopSound()
	{
		if ( GetGame().IsClient()  ||  !GetGame().IsMultiplayer() )
		{
			if (m_AlarmLoopStartTimer)
			{
				m_AlarmLoopStartTimer.Stop();
			}

			if (m_AlarmLoop){
				if (m_AlarmLoop.IsSoundPlaying()) m_AlarmLoop.SoundStop();
			}
		}
	}
}
