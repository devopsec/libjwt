/* Public domain, no copyright. Use at your own risk. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <jwt.h>

static void jwt_exit(void)
{
	perror("testjwt:");
	exit(1);
}

int main(int argc, char *argv[])
{
	jwt_t *jwt, *new;
	unsigned char key256[32] = "012345678901234567890123456789XY";
	unsigned char key384[48] = "aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllll";

	if (jwt_new(&jwt))
		jwt_exit();

	if (jwt_add_grant(jwt, "iss", "files.cyphre.com"))
		jwt_exit();

	if (jwt_add_grant(jwt, "sub", "user0"))
		jwt_exit();

	if (jwt_add_grant(jwt, "ref", "XXX-111-222-444-666"))
		jwt_exit();

	if (jwt_add_grant(jwt, "ref", "11212lkjke1el1e12lk")) {
		printf("Passed duplicate grant check.\n");
	} else {
		fprintf(stderr, "FAILED duplicate grant check.\n");
		exit(2);
	}

	jwt_dump_fp(jwt, stdout, 1);

	jwt_del_grant(jwt, "ref");

	jwt_dump_fp(jwt, stdout, 0);
	putc('\n', stdout);

	jwt_encode_fp(jwt, stdout);
	putc('\n', stdout);

	jwt_set_alg(jwt, JWT_ALG_HS256, key256, sizeof(key256));

	jwt_dump_fp(jwt, stdout, 1);
	jwt_dump_fp(jwt, stdout, 0);
	putc('\n', stdout);
	jwt_encode_fp(jwt, stdout);
	putc('\n', stdout);

	new = jwt_dup(jwt);
	if (!new)
		jwt_exit();

	jwt_set_alg(new, JWT_ALG_HS384, key384, sizeof(key384));
	jwt_encode_fp(new, stdout);
	putc('\n', stdout);

	jwt_free(new);
	jwt_free(jwt);

	exit(0);
}