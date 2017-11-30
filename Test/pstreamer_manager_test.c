/*
 *
 *  copyright (c) 2017 luca baldesi
 *
 */

#include<assert.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include"pstreamer.h"


void pstreamer_manager_destroy_test()
{
	struct pstreamer_manager * psm = NULL;

	pstreamer_manager_destroy(NULL);
	pstreamer_manager_destroy(&psm);

	psm = pstreamer_manager_new(6000, NULL);

	pstreamer_manager_destroy(&psm);

	fprintf(stderr,"%s successfully passed!\n",__func__);
}

void pstreamer_manager_create_streamer_test()
{
	struct pstreamer_manager * psm = NULL;
	const struct pstreamer * ps = NULL;

	ps = pstreamer_manager_create_streamer(NULL, NULL, NULL, NULL, NULL, NULL);
	assert(ps == NULL);

	psm = pstreamer_manager_new(6000, NULL);

	ps = pstreamer_manager_create_streamer(psm, NULL, NULL, NULL, NULL, NULL);
	assert(ps == NULL);

	ps = pstreamer_manager_create_streamer(psm, "10.0.0.1", "6000", "42", "127.0.0.1", NULL);
	assert(ps);

	ps = pstreamer_manager_create_streamer(psm, "10.0.0.1", "6000", "24", "127.0.0.1", NULL);
	assert(ps);

	ps = pstreamer_manager_create_streamer(psm, "10.0.0.1", "6000", "42", "127.0.0.1", NULL);
	assert(ps == NULL);

	pstreamer_manager_destroy(&psm);

	fprintf(stderr,"%s successfully passed!\n",__func__);
}

void pstreamer_to_json_test()
{
	struct pstreamer_manager * psm = NULL;
	const struct pstreamer * ps = NULL;
	char * json = NULL;

	json = pstreamer_to_json(NULL);
	assert(json == NULL);

	psm = pstreamer_manager_new(6000, NULL);
	ps = pstreamer_manager_create_streamer(psm, "10.0.0.1", "6000", "42", "127.0.0.1", NULL);

	json = pstreamer_to_json(ps);
	fprintf(stderr, "[DEBUG] %s\n", json);
	assert(strcmp(json, "{\"id\":\"42\",\"source_ip\":\"10.0.0.1\",\"source_port\":\"6000\",\"janus_streaming_id\":\"0\"}") == 0);
	free(json);

	pstreamer_manager_destroy(&psm);
	fprintf(stderr,"%s successfully passed!\n",__func__);
}

void pstreamer_manager_destroy_streamer_test()
{
	struct pstreamer_manager * psm = NULL;
	const struct pstreamer * ps = NULL;
	uint8_t res;

	res = pstreamer_manager_destroy_streamer(NULL, NULL);
	assert(res);

	psm = pstreamer_manager_new(6000, NULL);
	res = pstreamer_manager_destroy_streamer(psm, NULL);
	assert(res);

	ps = pstreamer_manager_create_streamer(psm, "10.0.0.1", "6000", "42", "127.0.0.1", NULL);
	ps = pstreamer_manager_create_streamer(psm, "10.0.0.1", "6000", "24", "127.0.0.1", NULL);

	res = pstreamer_manager_destroy_streamer(psm, ps);
	assert(res == 0);

	pstreamer_manager_destroy(&psm);

	fprintf(stderr,"%s successfully passed!\n",__func__);
}

void pstreamer_manager_set_streamer_options_test()
{
	struct pstreamer_manager * psm = NULL;
	int8_t res;

	res = pstreamer_manager_set_streamer_options(psm, NULL);
	assert(res == -1);

	psm = pstreamer_manager_new(6000, NULL);

	res = pstreamer_manager_set_streamer_options(psm, NULL);
	assert(res == -1);

	res = pstreamer_manager_set_streamer_options(psm, "iface=lo");
	assert(res == 0);

	pstreamer_manager_create_streamer(psm, "10.0.0.1", "6000", "42", "127.0.0.1", NULL);
	pstreamer_manager_destroy(&psm);
	fprintf(stderr,"%s successfully passed!\n",__func__);
}

int main(int argv, char ** argc)
{
	pstreamer_manager_destroy_test();
	pstreamer_manager_create_streamer_test();
	pstreamer_to_json_test();
	pstreamer_manager_destroy_streamer_test();
	pstreamer_manager_set_streamer_options_test();
	return 0;
}
