//
//  Download.c
//  R_TTS
//
//  Created by RocKK on 12/19/13.
//  Copyright (c) 2013 RocKK.
//  All rights reserved.
//
//  Redistribution and use in source and binary forms are permitted
//  provided that the above copyright notice and this paragraph are
//  duplicated in all such forms and that any documentation,
//  advertising materials, and other materials related to such
//  distribution and use acknowledge that the software was developed
//  by the RocKK.  The name of the
//  RocKK may not be used to endorse or promote products derived
//  from this software without specific prior written permission.
//  THIS SOFTWARE IS PROVIDED ''AS IS'' AND WITHOUT ANY EXPRESS OR
//  IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

#include <stdio.h>
#include <curl/curl.h>
 
//=================================================//

struct HttpFile {
  const char *filename;
  FILE *stream;
};

//=================================================//

static size_t my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream)
{
  struct HttpFile *out=(struct HttpFile *)stream;
  if(out && !out->stream) {
    /* open file for writing */
    out->stream=fopen(out->filename, "wb");
    if(!out->stream)
      return -1; /* failure, can't open file to write */
  }
  return fwrite(buffer, size, nmemb, out->stream);
}

//=================================================//

void downloadFileWithNameFromUrl(const char* name, const char* url)
{
  CURL *curl;
  CURLcode res;
  struct HttpFile httpFile={
    name, /* name to store the file as if succesful */
    NULL
  };

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();
  if(curl) {
    /*You better replace the URL with one that works!*/
    curl_easy_setopt(curl, CURLOPT_URL, url);
    /* Define our callback to get called when there's data to be written */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
     //Set a pointer to our struct to pass to the callback 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &httpFile);

    /* Switch on full protocol/debug output */
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    res = curl_easy_perform(curl);

    /* always cleanup */
    curl_easy_cleanup(curl);

    if(CURLE_OK != res) {
      /* we failed */
      fprintf(stderr, "curl told us %d\n", res);
    }
  }

  if(httpFile.stream)
    fclose(httpFile.stream); /* close the local file */

  curl_global_cleanup();
}

//=================================================//