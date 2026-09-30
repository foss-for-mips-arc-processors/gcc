/* { dg-do assemble } */
/* { dg-require-effective-target hs6x } */
/* { dg-options "-O2 -std=gnu99" } */

void wake (void);

int initialized_sr;
int initialized_srl;
void *volatile notification;

#define REPEAT_13(STORE) \
  STORE;		 \
  STORE;		 \
  STORE;		 \
  STORE;		 \
  STORE;		 \
  STORE;		 \
  STORE;		 \
  STORE;		 \
  STORE;		 \
  STORE;		 \
  STORE;		 \
  STORE;		 \
  STORE

static inline void
initialize_sr (void)
{
  REPEAT_13 (__builtin_arc_sr (0, 3329));
  initialized_sr = 1;
}

static inline void
handle_sr (void)
{
  unsigned int status = __builtin_arc_lr (3341) & 7;
  if (status == 0)
    return;
  __builtin_arc_sr (status, 3342);
  if (notification != 0)
    wake ();
}

void
trigger_sr (void)
{
  if (!initialized_sr)
    initialize_sr ();
  handle_sr ();
}

static inline void
initialize_srl (void)
{
  REPEAT_13 (__builtin_arc_srl (0, 3329));
  initialized_srl = 1;
}

static inline void
handle_srl (void)
{
  unsigned long status = __builtin_arc_lrl (3341) & 7;
  if (status == 0)
    return;
  __builtin_arc_srl (status, 3342);
  if (notification != 0)
    wake ();
}

void
trigger_srl (void)
{
  if (!initialized_srl)
    initialize_srl ();
  handle_srl ();
}
