/*  -*- coding: utf-8 -*-   */

#include <stdio.h>
#include <stdlib.h>  /* exit, atoi */
#include <string.h>
#include <strings.h>
#include <dirent.h>  /* opendir, readdir */

#include <libexif/exif-data.h>

/* see exif-tag.c for more */
struct exif_data {
  char exposure_time[32];
  char f_number[32];
  char date_time_original[32];
};

void
print_usage(char *progname) {
  printf("Usage: %s DIRECTORY_WITH_JPEGS\n", progname);
}

/* see the implementation of exif_entry_dump() */
void
read_exif_data_from_file(const char *filename, struct exif_data *edata_p) {
  char value[1024];
  unsigned int i;
  ExifData *ed = exif_data_new_from_file(filename);
  ExifContent *ec = ed->ifd[EXIF_IFD_EXIF];

  edata_p->exposure_time[0] = '\0';
  edata_p->f_number[0] = '\0';
  edata_p->date_time_original[0] = '\0';

  for (i = 0; i < ec->count; i++) {
    ExifEntry *ee = ec->entries[i];
    const char *tag_name = exif_tag_get_name(ee->tag);

    /* exif_entry_dump(ee, 4); */

    if (strcmp("ExposureTime", tag_name) == 0) {
      strcpy(edata_p->exposure_time, exif_entry_get_value(ee, value, sizeof(value)));
    }
    if (strcmp("FNumber", tag_name) == 0) {
      strcpy(edata_p->f_number, exif_entry_get_value(ee, value, sizeof(value)));
    }
    if (strcmp("DateTimeOriginal", tag_name) == 0) {
      strcpy(edata_p->date_time_original, exif_entry_get_value(ee, value, sizeof(value)));
    }
  }
  return;
}

/*   YAML

- :fnumber: f/4.0
  :filename: 08100015.jpg
- :fnumber: f/2.6
  :filename: 08100016.jpg
- :fnumber: f/8.0
  :filename: 08100017.jpg

     Ruby (tablica haszy):

[
  { :filename => '08100015.jpg', :fnumber => 'f/4.0'},
  { :filename => '08100016.jpg', :fnumber => 'f/2.6'},
  { :filename => '08100017.jpg', :fnumber => 'f/8.0'},
]

*/

void
yaml_print_data(const char *filename, const char *dir, struct exif_data edata, int height, int width) {
  printf("- :filename: %s\n", filename);
  printf("  :title: %s\n", filename);
  printf("  :exposuretime: %s\n", edata.exposure_time);
  printf("  :fnumber: %s\n", edata.f_number);
  printf("  :datetimeoriginal: %s\n", edata.date_time_original);
  printf("  :dir: %s\n", dir);
}

void
yaml_print_comment(char *comment) {
  printf("#  directory:  %s\n", comment);
}

int
main(int argc, char **argv) {
    DIR *dir_p;
    struct dirent *dir_entry_p;

    if (2 != argc) {
      print_usage(argv[0]);
      exit(1);
    }
    if (NULL == (dir_p = opendir(argv[1]))) {
      printf("! can't open directory: %s\n", argv[1]);
      exit(2);
    }

    while (NULL != (dir_entry_p = readdir(dir_p))) { /* read each entry until NULL */
      char buf[1024];
      char *filename = dir_entry_p->d_name;
      size_t len = strlen(filename);
      struct exif_data edata;
      int height, width;

      if (filename[0] == '.' || len < 5)
        continue;
      if (strcasecmp(".jpg", filename+(len-4)) == 0)  {
        char *dirname = argv[1];
        strcpy(buf, argv[1]);
        if (dirname[strlen(dirname)-1] != '/')
          strcat(buf, "/");
        strcat(buf, filename);
        read_exif_data_from_file(buf, &edata);
        yaml_print_data(filename, argv[1], edata, height, width);
      }
    }
    closedir(dir_p);

    return EXIT_SUCCESS;
}


/* jak odczytać wymiary bezpośrednio za pomocą biblioteki Exif.
   jeśli zdjęcie jest portretowe (a nie pejzażowe)
   to odczytana wysokość jest szerokością zdjęcia
   a odczytana szerokość jest wysokością zdjęcia.
   przynajmniej tak było w 2006 roku.

extern FILE *popen(const char *command, const char *type);
extern int pclose(FILE *stream);

read_jpeg_dimensions_from_file(buf, &height, &width);

void
read_jpeg_dimensions_from_file(const char *filename, int *height, int *width) {
  FILE *fp;
  char buf[1024];
  char cmd[1024];

  strcpy(cmd, "/usr/bin/identify ");
  strcat(cmd, filename);

  fp = popen(cmd, "r");
  if (NULL != fgets(buf, sizeof buf, fp)) {
    int ic = sscanf(buf, "%*s JPEG %dx%d", width, height);
    if (ic != 2) {
      fprintf(stderr, "! warning: unable to read jpg dimension from: %s\n", filename);
      *width = *height = 0;
    }
  }
  pclose(fp);

  return;
}

*/
