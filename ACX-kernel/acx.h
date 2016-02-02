/**
 * acx.h
 * System configuration for a basic cooperative executive
 * Kernel.
 * @author Christopher Waldon
 */

/*
 * Define system constants
 */
#define x_getTID() 	(x_thread_id)
#define MAX_THREADS	8
#define NUM_THREADS	8
typedef uint8_t		byte;
typedef uint8_t		bool;
typedef void		(*PTHREAD)(void);

/*
 * Define the starting size of the stacks
 */
#define DEFAULT_SIZE	128
#define TH0_SIZE	DEFAULT_SIZE
#define TH1_SIZE	DEFAULT_SIZE
#define TH2_SIZE	DEFAULT_SIZE
#define TH3_SIZE	DEFAULT_SIZE
#define TH4_SIZE	DEFAULT_SIZE
#define TH5_SIZE	DEFAULT_SIZE
#define TH6_SIZE	DEFAULT_SIZE
#define TH7_SIZE	DEFAULT_SIZE

/*
 * Define the starting locations of the stacks
 */
#define STACK_START	0x21FF
#define INIT_SPACE	0x80
#define TH0_START	(INIT_SPACE+STACK_START)
#define TH1_START	(TH0_START+TH0_SIZE)
#define TH2_START	(TH1_START+TH1_SIZE)
#define TH3_START	(TH2_START+TH2_SIZE)
#define TH4_START	(TH3_START+TH3_SIZE)
#define TH5_START	(TH4_START+TH4_SIZE)
#define TH6_START	(TH5_START+TH5_SIZE)
#define TH7_START	(TH6_START+TH6_SIZE)

/*
 * Define the positions of each canary
 */
#define TH0_CANARY	(TH1_START-1)
#define TH1_CANARY	(TH2_START-1)
#define TH2_CANARY	(TH3_START-1)
#define TH3_CANARY	(TH4_START-1)
#define TH4_CANARY	(TH5_START-1)
#define TH5_CANARY	(TH6_START-1)
#define TH6_CANARY	(TH7_START-1)
#define TH7_CANARY	(TH7_START+TH7_SIZE-1)

/*
 * Define ACX function prototypes
 */
void x_init();
void x_new(byte tid, PTHREAD pthread, byte isEnabled);
void X_yield();
void x_delay(int ticks);
void x_suspend(int tid);
void x_resume(int tid);
void x_disable(int tid);
void x_enable(int tid);
long gtime();

/*********************************************************|
 * Define stack control structures ***********************|
 */

/**
 * Stack stores the base address of a given stack, as well as
 * a pointer to the current head address of that stack.
 */
typedef struct {
	byte * pHead;
	byte * pBase;
} Stack;

/**
 * StackDelay represents a delay length for a single thread
 */
typedef uint16_t StackDelay;


