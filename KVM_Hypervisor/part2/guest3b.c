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

	/* Write code here */
	uint32_t buf[5] = {0};

	for (;;)
	{
		outl(0x11, (uint32_t)(uintptr_t)buf);
		outl(0x12, (uint32_t)(uintptr_t)buf);
	}

	*(long *)0x400 = 42;

	for (;;)
		asm("hlt" : /* empty */ : "a"(42) : "memory");
}
