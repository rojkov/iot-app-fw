/*
 * Copyright (c) 2015, Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Intel Corporation nor the names of its contributors
 *     may be used to endorse or promote products derived from this software
 *     without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "generator.h"

int template_load(generator_t *g)
{
    char **errors;

    g->template = smpl_load_template(g->path_template, &errors);

    if (g->template != NULL)
        return 0;
    else {
        int i;

        log_error("Failed to load template file '%s'.", g->path_template);

        if (errors != NULL) {
            for (i = 0; errors[i] != NULL; i++)
                log_error("error: %s", errors[i]);
            smpl_errors_free(errors);
        }

        return -1;
    }
}


int template_eval(service_t *s)
{
    char **errors;

    s->output = smpl_evaluate(s->g->template, s->data, &errors);

    if (s->output != NULL)
        return 0;
    else {
        int i;

        log_error("Failed to generate service file for %s / %s.",
                  s->provider, s->app);

        if (errors != NULL) {
            for (i = 0; errors[i] != NULL; i++)
                log_error("error: %s", errors[i]);
            smpl_errors_free(errors);
        }

        return -1;
    }
}


