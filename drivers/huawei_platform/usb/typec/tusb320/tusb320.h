

#ifndef _TYPEC_TUSB320_H_
#define _TYPEC_TUSB320_H_

#define TUSB320_REGISTER_NUM    12

#ifndef BIT
#define BIT(x)        (1 << (x))
#endif

/* Register address */
#define TUSB320_REG_DEVICE_ID            0x00
#define TUSB320_REG_CURRENT_MODE         0x08
#define TUSB320_REG_ATTACH_STATUS        0x09
#define TUSB320_REG_MODE_SET             0x0a

/* Register REG_CURRENT_MODE 08 */
#define TUSB320_REG_HOST_CUR_MID                BIT(6)
#define TUSB320_REG_HOST_CUR_HIGH               BIT(7)
#define TUSB320_REG_HOST_CUR_MODE               (BIT(7) | BIT(6))
#define TUSB320_REG_HOST_CUR_DEFAULT            0x00
#define TUSB320_REG_DEV_CUR_MID                 BIT(4)
#define TUSB320_REG_DEV_CUR_HIGH                (BIT(5) | BIT(4))
#define TUSB320_REG_DEV_CUR_MODE                (BIT(5) | BIT(4))
#define TUSB320_REG_DEV_CUR_DEFAULT             0x00

/* Register REG_ATTACH_STATUS 09 */
#define TUSB320_REG_STATUS_DFP                  BIT(6)
#define TUSB320_REG_STATUS_UFP                  BIT(7)
#define TUSB320_REG_STATUS_MODE                 (BIT(7) | BIT(6))
#define TUSB320_REG_STATUS_CC                   BIT(5)
#define TUSB320_REG_STATUS_INT                  BIT(4)

/* Register REG_MODE_SET 0a */
#define TUSB320_REG_SET_UFP                     BIT(4)
#define TUSB320_REG_SET_DFP                     BIT(5)
#define TUSB320_REG_SET_DRP                     (BIT(5) | BIT(4))
#define TUSB320_REG_SET_DEFAULT                 0x00
#define TUSB320_REG_SET_PORT_MODE               (BIT(5) | BIT(4))


#endif /*_TYPEC_TUSB320_H_*/
