
#define SIM1 "SIM1"
#define SIM2 "SIM2"

//#define SIM_HPD

/*sim����λ��ƽֵ*/
#define HIGH_LEVEL 1
#define LOW_LEVEL 0

#define HISI_SIM_MAX 2

/*GPIO����ʱ��*/
#define SIM_DEBOUNCE_TIME   (10) 

struct balong_sim_plat_data{
    char * name;
    unsigned int sim_detection_gpio;
    unsigned int sim_status;
};
