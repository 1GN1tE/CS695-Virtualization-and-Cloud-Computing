#include <stddef.h>
#include <stdint.h>

static void outl(uint16_t port, uint32_t value)
{
	asm("outl %0,%1" : /* empty */ : "a"(value), "Nd"(port) : "memory");
}

void
	__attribute__((noreturn))
	__attribute__((section(".start")))
	_start(void)
{

	/* write code here */
	uint32_t buf[5] = {0};

	uint32_t i = 0;
	for (;;)
	{
		buf[i % 5] = i;
		if (i++ % 5 == 4)
		{
			outl(0x10, (uint32_t)(uintptr_t)buf);
		}
	}

	*(long *)0x400 = 42;

	for (;;)
		asm("hlt" : /* empty */ : "a"(42) : "memory");
}
