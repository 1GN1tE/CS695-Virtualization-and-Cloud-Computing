#include <stddef.h>
#include <stdint.h>

#define BUF_SIZE 20

static void outl(uint16_t port, uint32_t value)
{
	asm volatile("outl %0,%1" : /* empty */ : "a"(value), "Nd"(port) : "memory");
}

static uint32_t inl(uint16_t port)
{
	uint32_t value;
	asm volatile("inl %1,%0" : "=a"(value) : "Nd"(port) : "memory");
	return value;
}

static uint32_t getRandom()
{
	uint32_t value;
	asm volatile("rdtsc" : "=a"(value));
	return value;
}

void
	__attribute__((noreturn))
	__attribute__((section(".start")))
	_start(void)
{

	/* Write code here */
	int32_t buf[BUF_SIZE] = {0};
	int32_t prod_p, cons_p;

	outl(0x15, (uint32_t)(uintptr_t)buf);

	for (;;)
	{
		/* recv prod_p and cons_p */
		prod_p = inl(0x10);
		cons_p = inl(0x11);

		uint32_t r = getRandom(), value;

		/* number of items produced in range [0, 10] */
		r = r % 11;

		/* produce values */
		for (int i = 0; i < r; i++)
		{
			if ((prod_p + 1) % BUF_SIZE == cons_p || (cons_p == -1 && (prod_p + 1) == BUF_SIZE))
			{
				break;
			}

			prod_p = (prod_p + 1) % BUF_SIZE;
			value = getRandom();
			/* produced value in range [0, 10] */
			buf[prod_p] = value % 11;
		}

		/* send updated prod_p */
		outl(0x13, prod_p);
	}

	*(long *)0x400 = 42;

	for (;;)
		asm("hlt" : /* empty */ : "a"(42) : "memory");
}
