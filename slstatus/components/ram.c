/* See LICENSE file for copyright and license details. */
#include <stdio.h>

#include "../util.h"

#if defined(__linux__)
	const char *
	ram_free(void)
	{
		long free;

		if (pscanf("/proc/meminfo",
		           "MemTotal: %ld kB\n"
		           "MemFree: %ld kB\n"
		           "MemAvailable: %ld kB\n",
		           &free, &free, &free) != 3) {
			return NULL;
		}

		return fmt_human(free * 1024, 1024);
	}

	const char *
	ram_perc(void)
	{
		long total, free, buffers, cached;

		if (pscanf("/proc/meminfo",
		           "MemTotal: %ld kB\n"
		           "MemFree: %ld kB\n"
		           "MemAvailable: %ld kB\nBuffers: %ld kB\n"
		           "Cached: %ld kB\n",
		           &total, &free, &buffers, &buffers, &cached) != 5) {
			return NULL;
		}

		return bprintf("%d", 100 * ((total - free) -
		                            (buffers + cached)) / total);
	}

	const char *
	ram_total(void)
	{
		long total;

		if (pscanf("/proc/meminfo", "MemTotal: %ld kB\n",
		           &total) != 1) {
			return NULL;
		}

		return fmt_human(total * 1024, 1024);
	}

	const char *
	ram_used(void)
	{
		long total, free, buffers, cached;

		if (pscanf("/proc/meminfo",
		           "MemTotal: %ld kB\n"
		           "MemFree: %ld kB\n"
		           "MemAvailable: %ld kB\nBuffers: %ld kB\n"
		           "Cached: %ld kB\n",
		           &total, &free, &buffers, &buffers, &cached) != 5) {
			return NULL;
		}

		return fmt_human((total - free - buffers - cached) * 1024,
		                 1024);
	}
#elif defined(__OpenBSD__)
	#include <stdlib.h>
	#include <sys/sysctl.h>
	#include <sys/types.h>
	#include <unistd.h>

	#define LOG1024 	10
	#define pagetok(size, pageshift) (size_t)(size << (pageshift - LOG1024))

	inline int
	load_uvmexp(struct uvmexp *uvmexp)
	{
		int uvmexp_mib[] = {CTL_VM, VM_UVMEXP};
		size_t size;

		size = sizeof(*uvmexp);

		if (sysctl(uvmexp_mib, 2, uvmexp, &size, NULL, 0) >= 0) {
			return 1;
		}

		return 0;
	}

	const char *
	ram_free(void)
	{
		struct uvmexp uvmexp;
		int free_pages;

		if (load_uvmexp(&uvmexp)) {
			free_pages = uvmexp.npages - uvmexp.active;
			return fmt_human(pagetok(free_pages, uvmexp.pageshift) *
			                 1024, 1024);
		}

		return NULL;
	}

	const char *
	ram_perc(void)
	{
		struct uvmexp uvmexp;
		int percent;

		if (load_uvmexp(&uvmexp)) {
			percent = uvmexp.active * 100 / uvmexp.npages;
			return bprintf("%d", percent);
		}

		return NULL;
	}

	const char *
	ram_total(void)
	{
		struct uvmexp uvmexp;

		if (load_uvmexp(&uvmexp)) {
			return fmt_human(pagetok(uvmexp.npages,
			                         uvmexp.pageshift) * 1024,
			                 1024);
		}

		return NULL;
	}

	const char *
	ram_used(void)
	{
		struct uvmexp uvmexp;

		if (load_uvmexp(&uvmexp)) {
			return fmt_human(pagetok(uvmexp.active,
			                         uvmexp.pageshift) * 1024,
			                 1024);
		}

		return NULL;
	}
#endif
