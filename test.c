typedef enum
{
    E_INPUT_STATE_ASSERTED_U = 0u,
    E_INPUT_STATE_RELEASED_U
}EInputState_t;

typedef enum
{
    E_INPUT_EV_NONE_U           = 0u,
    E_INPUT_EV_SHORT_PRESS_U,
    E_INPUT_EV_LONG_PRESS_U
}EInputEvent_t;

static EInputState_t            cefcc_eInputState;
static volatile EInputEvent_t   cefcc_veInputEvent;

void cefcc_fnLongPressTimeoutCb_vo(void)
{
    cefcc_veInputEvent = E_INPUT_EV_LONG_PRESS_U;

    OS_SIGNAL(EVENT();
}

void cefcc_fnProcessInputEvent_vo(void)
{
    EInputState_t eInputState;

    STOP_TIMER();

    eInputState = (EInputState_t)read_input();

    if(cefcc_eInputState != eInputState)
    {
        if(E_TRUE_U == cefcc_fnDebounceFilterPassed_b())
        {
            cefcc_eInputState = eInputState;

            if(E_INPUT_STATE_ASSERTED_U == cefcc_eInputState)
            {
                /* Pressed */
                cefcc_u32StartTime = cefcc_fnGetTime_u32();
                
                SET_MSEC_TIMER();
            }
            else
            {
                /* Released */
                           
                cefcc_u32ElapsedTime = cefcc_fnGetTime_u32() - cefcc_u32StartTime;            
            }
        }
    }

    if(E_INPUT_EV_NONE_U != cefcc_veInputEvent)
    {
        if(E_INPUT_EV_SHORT_PRESS_U == eInputEvent)
        {
            /* Signal sleep action */
        }
        else
        {
            /* Signal abort action */
        }

        eInputEvent = E_INPUT_EVENT_NONE_U;
    }
}



/* Debounce */   
    startTime = cefcc_fnGetTime_u32();

    do
    {
        HAL_fnDelayMsec_vo(5u);

        new_read = IS_GPIO_ASSERTED();
        
        u32ElapsedTime = cefcc_fnGetTime_u32() - startTime;      
        
    } while((new_read != pre_read) && (_DEBOUNCE_TIME_IN_MS > u32ElapsedTime));

    if(u32ElapsedTime >= _DEBOUNCE_TIME_IN_MS)
    {
        pre_read = new_read;

        if(PUSHED == pre_read)
        {
            button_stat;
            SET_TIMER_MSEC(&tim_push, LONG_PRESS_TIMEOUT);
        }
        else
        { /* Released */
            if(E_TRUE_U; == OS_Timer_Is_Active())
            {
                STOP_TIMER(&tim_push);              
                event = SHORT_PUSH;
            }
            else
            {

            }
        }
    }
}