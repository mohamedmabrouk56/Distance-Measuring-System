/**
 * @file 	timer.c
 * @brief TIMER Source file.
 *
 * This file contains The Implementation of Functions of the TIMER module
  *
  * @author [Mohamed Mabrouk]
  * @date [25 JAN 2024]
  *
  * @SWversion 1.0.0
  *
  * @remarks
  *    -Platform         : AVR
  *    -Peripherial      : Atmega32
  */
  /*==================================================================================================================================*/

 /* ===================================================================================================
											  Includes
	===================================================================================================*/
#include"timer.h"
#include"gpio.h"
#include"timer_Regs.h"
#include"common_macros.h"
	/* ===================================================================================================
											  Global Variables
	   ===================================================================================================*/

/*Global Pointer to function*/
static volatile void (*TIMER0_PtrCallBack)(void) = NULL_PTR;
static volatile void (*TIMER1_PtrCallBack)(void) = NULL_PTR;
static volatile void (*TIMER2_PtrCallBack)(void) = NULL_PTR;

uint8 Timer1_Mode;

/* ===================================================================================================
										  Function Definition
   ===================================================================================================*/

/**
 *
 * This Function responsible for initialize the TIMER driver.
 *
 * @param[in]  Config_Ptr Type TIMER_ConfigType
 * @param[out] none
 * @return none
 */
void TIMER_init(const TIMER_ConfigType *Config_Ptr)
{
	int i;
	for(i=0;i<NUMBER_OF_USED_TIMERS;i++)
	{
	switch(Config_Ptr->Units[i].TimerNum)
	{
	case TIMER0:
	TCCR0 |= Config_Ptr->Units[i].Prescaler;
	switch(Config_Ptr->Units[i].Mode)
	{
	case TIMER0_OVF:
	/* Choose the Normal Mode  */
	CLR_BIT(TCCR0, WGM00);
	CLR_BIT(TCCR0, WGM01);

	/* Enabling the Overflow Interrupt Enable */
	TIMSK = (TIMSK & 0xFC) | (1 << TOIE0);
	/* Enabling the FOCO As i Choose Non Pwm Mode */
	SET_BIT(TCCR0, FOC0);
	break;

	case  TIMER0_CTC:
	/* Choose the Compare Match Mode */
	CLR_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);

	/* Choose the OCO State in CTC */
	TCCR0 = (TCCR0 & 0xCF) | ((Config_Ptr->Units[i].CtcMode)<<COM00) ;

	/* Enabling the CTC Interrupt Enable */
	TIMSK = (TIMSK & 0xFC) | (1 << OCIE0);
	/* Enabling the FOCO As To Choose Non Pwm Mode */
	SET_BIT(TCCR0, FOC0);
	break;

	case  TIMER0_FAST_PWM:
	/* Choose the FAST PWM */
	SET_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);

	/* Choose the Fast Pwm Working Mode */
	TCCR0 = (TCCR0 & 0xCF) | ((Config_Ptr->Units[i].PwmMode)<<COM00) ;

	/* Disabling the CTC , Overflow Interrupt Enable */
	TIMSK = (TIMSK & 0xFC);

	/* Disabling the FOCO As To Choose a Pwm Mode */
	CLR_BIT(TCCR0, FOC0);

	/* Defining OC0 Pin As an Output */
	GPIO_setupPinDirection(PORTD_ID, PIN3_ID, PIN_OUTPUT);
	break;

	case TIMER0_PHASE_PWM:
	/* Choose the PHASE PWM Mode */
	SET_BIT(TCCR0, WGM00);
	CLR_BIT(TCCR0, WGM01);

	/* Defining OC0 Pin As an Output */
	GPIO_setupPinDirection(PORTD_ID, PIN3_ID, PIN_OUTPUT);
	break;

	default :
		/* Wrong Input */
	break;

	}

	break;
	case TIMER1:
		TCCR1B |= Config_Ptr->Units[i].Prescaler;
		Timer1_Mode = Config_Ptr->Units[i].Mode;
		switch(Config_Ptr->Units[i].Mode)
		{
		case TIMER1_OVF:
		/* Choose the Mode */
		CLR_BIT(TCCR1A, WGM10);
		CLR_BIT(TCCR1A, WGM11);
		CLR_BIT(TCCR1B, WGM12);
		CLR_BIT(TCCR1B, WGM13);

		/* Enabling the FOC1A & FOC1B To Choose Non Pwm Mode */
		SET_BIT(TCCR1A, FOC1A);
		SET_BIT(TCCR1A, FOC1B);

		/* Enabling the Overflow Interrupt Enable */
		TIMSK = (TIMSK & 0xE3)  | (1 << TOIE1);

		break;
		case  TIMER1_CTC_OCR:
		/* Choose the CTC Mode With OCR */
		CLR_BIT(TCCR1A, WGM10);
		CLR_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		CLR_BIT(TCCR1B, WGM13);

		/* Enabling the FOC1A & FOC1B To Choose Non Pwm Mode */
		SET_BIT(TCCR1A, FOC1A);
		SET_BIT(TCCR1A, FOC1B);

		/* Enabling the Overflow Interrupt Enable */
		TIMSK = (TIMSK & 0xE3)  | (1 << OCIE1A);

		/* Choose the OC1A , OC1B State in CTC */
		TCCR1A = (TCCR0 & 0x0F) | ((Config_Ptr->Units[i].CtcMode)<<COM1B0) | ((Config_Ptr->Units[i].CtcMode)<<COM1A0);
		break;

		case   TIMER1_FAST_PWM_8BIT :
		/* Choose the Fast Pwm With 8bit Range */
		SET_BIT(TCCR1A, WGM10);
		CLR_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		CLR_BIT(TCCR1B, WGM13);

		/* Choose the PWM Working Mode */
		TCCR1A = (TCCR0 & 0x0F) | ((Config_Ptr->Units[i].PwmMode)<<COM1B0) | ((Config_Ptr->Units[i].PwmMode)<<COM1A0);

		/* Defining OC1A / OC1B Pin As an Output */
		GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_OUTPUT);
		GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
		break;

		case    TIMER1_FAST_PWM_9BIT :
		/* Choose the Fast Pwm With 9bit Range */
		CLR_BIT(TCCR1A, WGM10);
		SET_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		CLR_BIT(TCCR1B, WGM13);

		/* Choose the PWM Working Mode */
		TCCR1A = (TCCR0 & 0x0F) | ((Config_Ptr->Units[i].PwmMode)<<COM1B0) | ((Config_Ptr->Units[i].PwmMode)<<COM1A0);

		/* Defining OC1A / OC1B Pin As an Output */
		GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_OUTPUT);
		GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
		break;

		case    TIMER1_FAST_PWM_10BIT :
		/* Choose the Fast Pwm With 10bit Range */
		SET_BIT(TCCR1A, WGM10);
		SET_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		CLR_BIT(TCCR1B, WGM13);

		/* Choose the PWM Working Mode */
		TCCR1A = (TCCR0 & 0x0F) | ((Config_Ptr->Units[i].PwmMode)<<COM1B0) | ((Config_Ptr->Units[i].PwmMode)<<COM1A0);

		/* Defining OC1A / OC1B Pin As an Output */
		GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_OUTPUT);
		GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
		break;

		case    TIMER1_CTC_ICR :
		/* Choose the CTC Mode With ICR */
		CLR_BIT(TCCR1A, WGM10);
		CLR_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		SET_BIT(TCCR1B, WGM13);

		/* Enabling the FOC1A & FOC1B To Choose Non Pwm Mode */
		SET_BIT(TCCR1A, FOC1A);
		SET_BIT(TCCR1A, FOC1B);

		/* Enabling the Overflow Interrupt Enable */
		TIMSK = (TIMSK & 0xE3)  | (1 << OCIE1A);

		/* Choose the OC1A , OC1B State in CTC */
		TCCR1A = (TCCR0 & 0x0F) | ((Config_Ptr->Units[i].CtcMode)<<COM1B0) | ((Config_Ptr->Units[i].CtcMode)<<COM1A0);
		break;

		case    TIMER1_FAST_PWM_ICR	 :
		/* Choose the Fast Pwm With ICR REG */
		CLR_BIT(TCCR1A, WGM10);
		SET_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		SET_BIT(TCCR1B, WGM13);

		/* Choose the PWM Working Mode */
		TCCR1A = (TCCR0 & 0x0F) | ((Config_Ptr->Units[i].PwmMode)<<COM1B0) | ((Config_Ptr->Units[i].PwmMode)<<COM1A0);

		/* Defining ICR Pin As an Output */
		GPIO_setupPinDirection(PORTD_ID, PIN6_ID, PIN_OUTPUT);
		break;

		case	 TIMER1_FAST_PWM_OCR :
		/* Choose the Fast Pwm With 0CR REG */
		SET_BIT(TCCR1A, WGM10);
		SET_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		SET_BIT(TCCR1B, WGM13);

		/* Choose the PWM Working Mode */
		TCCR1A = (TCCR0 & 0x0F) | ((Config_Ptr->Units[i].PwmMode)<<COM1B0) | ((Config_Ptr->Units[i].PwmMode)<<COM1A0);

		/* Defining OC1A / OC1B Pin As an Output */
		GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_OUTPUT);
		GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
		break;

		default :
			/* Wrong Input */
			break;
		}
		break;

		/*Timer2 initiaillitation*/
	case TIMER2:
		TCCR2 |= Config_Ptr->Units[i].Prescaler;
		switch(Config_Ptr->Units[i].Mode)
			{
			case TIMER2_OVF:
			/* Choose the Normal Mode  */
			CLR_BIT(TCCR2, WGM20);
			CLR_BIT(TCCR2, WGM21);

			/* Enabling the Overflow Interrupt Enable */
			TIMSK = (TIMSK & 0x3F) | (1 << TOIE2);
			/* Enabling the FOC2 As To Choose Non Pwm Mode */
			SET_BIT(TCCR2, FOC2);
			break;

			case TIMER2_CTC:
			/* Choose the Compare Match Mode */
			CLR_BIT(TCCR2, WGM20);
			SET_BIT(TCCR2, WGM21);

			/* Enabling the Overflow Interrupt Enable */
			TIMSK = (TIMSK & 0x3F) | (1 << OCIE2);
			/* Enabling the FOC2 As To Choose Non Pwm Mode */
			SET_BIT(TCCR2, FOC2);
			break;

			case TIMER2_FAST_PWM :
			/* Choose the FAST PWM */
			SET_BIT(TCCR2, WGM20);
			SET_BIT(TCCR2, WGM21);

			/* Choose the Fast Pwm Working Mode */
			TCCR2 = (TCCR2 & 0xCF) | ((Config_Ptr->Units[i].PwmMode)<<COM20) ;

			/* Disabling the CTC , Overflow Interrupt Enable */
			TIMSK = (TIMSK & 0x3F);

			/* Disabling the FOCO As i Choose a Pwm Mode */
			CLR_BIT(TCCR2, FOC2);

			/* Defining OC2 Pin As an Output */
			GPIO_setupPinDirection(PORTD_ID, PIN7_ID, PIN_OUTPUT);
			break;

		    case TIMER2_PHASE_PWM :
		    /* Choose the Phase PWM */
			SET_BIT(TCCR2, WGM20);
			CLR_BIT(TCCR2, WGM21);

			/* Defining OC2 Pin As an Output */
			GPIO_setupPinDirection(PORTD_ID, PIN7_ID, PIN_OUTPUT);
			break;

		    default :
		    	/* Wrong Input */
		    break;
			}
		break;

		 default :
				 /* Wrong Timer Num */
		 break;
	}
	}
}

uint8 TIMER_read(Timer_ID Timer_num)
{
	switch(Timer_num)
	{
	case TIMER0:
	return TCNT0;
	break;
	case TIMER1:
	return TCNT1;
	break;
	case TIMER2:
	return TCNT2;
	break;
	default :
	  /* Wrong Timer Num */
	return 0;
	}

}

void TIMER_setPreloadValue (Timer_ID Timer_num,uint16 Preload)
{
	switch(Timer_num)
	{
   case TIMER0:
		TCNT0 = Preload;
   	break;
   	case TIMER1:
   		TCNT1 = Preload;
   	break;
   	case TIMER2:
   		TCNT2 = Preload;
   	break;
   	default :
   	  /* Wrong Timer Num */
   	break;
	}
}

void TIMER_setCompareMatch (Timer_ID Timer_num, uint16 Value)
{
	switch(Timer_num){

	case TIMER0:
		OCR0 = Value;
  	break;

  	case TIMER1:
if (Timer1_Mode ==  TIMER1_CTC_OCR)
	{
		OCR1A = Value;
	}
else if(Timer1_Mode ==  TIMER1_CTC_ICR)
	{
		ICR1 = Value;
	}
  	break;

  	case TIMER2:
  		OCR2 = Value;
  	break;

  	default :
  	/* Wrong Timer Num */
  	break;
	}
}

void TIMER_setCallBack(Timer_ID Timer_num , void (*copy_ptr)(void))
{
	switch(Timer_num)
	{
	case TIMER0:
		TIMER0_PtrCallBack = copy_ptr;
		break;
	case TIMER1:
		TIMER1_PtrCallBack = copy_ptr;
		break;
	case TIMER2:
		TIMER2_PtrCallBack = copy_ptr;
		break;
	default :
	  	/* Wrong Timer Num */
		break;
	}
}

/* TIMER 0*/
void TIMER0_setPwmDutyCycle (uint8 DutyCycle)
{
	OCR0 = (float32)((float32)DutyCycle/100)*255;
}


void TIMER1_setPwmDutyCycle (uint8 DutyCycle,uint8 Circuit)
{
if (Timer1_Mode == TIMER1_FAST_PWM_8BIT)
	{
	switch(Circuit)
		{
	case 1:
	OCR1A = (float32)((float32)DutyCycle/100)*255;
	break;
	case 2:
	OCR1B = (float32)((float32)DutyCycle/100)*255;
	break;
	default :
		/* Wrong Input */
	break;
		}
	}
else if (Timer1_Mode == TIMER1_FAST_PWM_9BIT)
	{
	switch(Circuit)
		{
	case 1:
	OCR1A = (float32)((float32)DutyCycle/100)*511;
	break;
	case 2:
	OCR1B = (float32)((float32)DutyCycle/100)*511;
	break;
	default :
	/* Wrong Input */
	break;
		}
	}
else if (Timer1_Mode == TIMER1_FAST_PWM_10BIT)
	{
	switch(Circuit)
		{
	case 1:
	OCR1A = (float32)((float32)DutyCycle/100)*1023;
	break;
	case 2:
	OCR1B = (float32)((float32)DutyCycle/100)*1023;
	break;
	default :
	/* Wrong Input */
	break;
		}
	}

else if (Timer1_Mode ==  TIMER1_FAST_PWM_ICR)
{
	ICR1 = 2499;
	OCR1A=DutyCycle;
}

else if (Timer1_Mode ==  TIMER1_FAST_PWM_OCR)
{
	OCR1A = 65535;
	OCR1B = (float32)((float32)DutyCycle/100)*65535;
}

}

void TIMER2_setPwmDutyCycle (uint8 DutyCycle)
{
	OCR2 = (float32)((float32)DutyCycle/100)*255;
}

/*ISR*/

void __vector_4(void) //TIMER2 COMP ISR 
{
//	static uint8 Local_Tick = 0;
	if (TIMER2_PtrCallBack != NULL_PTR)
			{
			TIMER2_PtrCallBack();
			}
	else
			{
			/* Do Nothing */
			}
}
void __vector_5(void) //TIMER2 OVF ISR
{
	if (TIMER2_PtrCallBack != NULL_PTR)
		{
			TIMER2_PtrCallBack();
		}
		else
		{
			/* Do Nothing */
		}
}


void __vector_7(void) /* TIMER1 COMPA ISR */
{
	//static uint16 Local_Tick = 0;
	if (TIMER1_PtrCallBack != NULL_PTR)
			{
	TIMER1_PtrCallBack();
			}
	else
			{
			/* Do Nothing */
			}

}
void __vector_8(void) /* TIMER1 COMPB ISR */
{
	//static uint16 Local_Tick = 0;
	TIMER1_PtrCallBack();
}
void __vector_9(void) //TIMER1 OVF ISR
{
	//static uint16 Local_Tick = 0;
	TIMER1_PtrCallBack();
}
void __vector_10(void) //TIMER0 COMP ISR 
{
	//static uint8 Local_Tick = 0;
	if (TIMER0_PtrCallBack != NULL_PTR)
			{
	TIMER0_PtrCallBack();
			}
	else
			{
			/* Do Nothing */
			}
}
void __vector_11(void) /* TIMER0 OVF ISR */
{

		if (TIMER0_PtrCallBack != NULL_PTR)
		{
			TIMER0_PtrCallBack();
		}
		else
		{
			/* Do Nothing */
		}
}

