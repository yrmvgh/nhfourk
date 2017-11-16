/* vim:set cin ft=c sw=4 sts=4 ts=8 et ai cino=Ls\:0t0(0 : -*- mode:c;fill-column:80;tab-width:8;c-basic-offset:4;indent-tabs-mode:nil;c-file-style:"k&r" -*-*/
/* Last modified by Jonadab the Unsightly One, 2017-Nov-14 */
/* NetHack may be freely redistributed.  See license for details. */
/* Copyright 1988, M. Stephenson */

#ifndef MONATTK_H
# define MONATTK_H

/*      Add new attack types below - ordering affects experience (exper.c).
 *      Attacks > AT_BUTT are worth extra experience.
 */
# define AT_ANY  (-1)   /* fake attack; dmgtype_fromattack wildcard */
# define AT_NONE 0      /* passive monster (ex. acid blob) */
# define AT_CLAW 1      /* claw (punch, hit, etc.) */
# define AT_BITE 2      /* bite */
# define AT_KICK 3      /* kick */
# define AT_BUTT 4      /* head butt (ex. a unicorn) */
# define AT_TUCH 5      /* touches */
# define AT_STNG 6      /* sting */
# define AT_HUGS 7      /* crushing bearhug */
# define AT_ERR8 8      /* (unused) */
# define AT_ERR9 9      /* (unused) */
# define AT_SPIT 10     /* spits substance - ranged */
# define AT_ENGL 11     /* engulf (swallow or by a cloud) */
# define AT_BREA 12     /* breath - ranged */
# define AT_EXPL 13     /* explodes - proximity */
# define AT_BOOM 14     /* explodes when killed */
# define AT_GAZE 15     /* gaze - ranged */
# define AT_TENT 16     /* tentacles */
# define AT_SPIN 17     /* web spinners */

# define LAST_CONTINUOUS_AT AT_SPIN

# define AT_WEAP 254    /* uses weapon */
# define AT_MAGC 255    /* uses magic spell(s) */

# define LAST_AT AT_MAGC

/*      Add new damage types below.
 *
 *      Note that 1-10 correspond to the types of attack used in buzz().
 *      Please don't disturb the order unless you rewrite the buzz() code.
 */
# define AD_ANY  (-1)   /* fake damage; attacktype_fordmg wildcard */
# define AD_PHYS 0      /* ordinary physical */
# define AD_MAGM 1      /* magic missiles */
# define AD_FIRE 2      /* fire damage */
# define AD_COLD 3      /* frost damage */
# define AD_SLEE 4      /* sleep ray */
# define AD_DISN 5      /* disintegration (death ray) */
# define AD_ELEC 6      /* shock damage */
# define AD_DRST 7      /* drains str (poison) */
# define AD_ACID 8      /* acid damage */
# define AD_SPC1 9      /* for extension of buzz() */
# define AD_SPC2 10     /* for extension of buzz() */
# define AD_BLND 11     /* blinds (yellow light) */
# define AD_STUN 12     /* stuns */
# define AD_SLOW 13     /* slows */
# define AD_PLYS 14     /* paralyses */
# define AD_DRLI 15     /* drains life levels (Vampire) */
# define AD_DREN 16     /* drains magic energy */
# define AD_LEGS 17     /* damages legs (xan) */
# define AD_STON 18     /* petrifies (Medusa, cockatrice) */
# define AD_STCK 19     /* sticks to you (mimic) */
# define AD_SGLD 20     /* steals gold (leppie) */
# define AD_SITM 21     /* steals item (nymphs) */
# define AD_SEDU 22     /* seduces & steals multiple items */
# define AD_TLPT 23     /* teleports you (Quantum Mech.) */
# define AD_RUST 24     /* rusts armor (Rust Monster) */
# define AD_CONF 25     /* confuses (Umber Hulk) */
# define AD_DGST 26     /* digests opponent (trapper, etc.) */
# define AD_HEAL 27     /* heals opponent's wounds (nurse) */
# define AD_WRAP 28     /* special "stick" for eels */
# define AD_WERE 29     /* confers lycanthropy */
# define AD_DRDX 30     /* drains dexterity (quasit) */
# define AD_DRCO 31     /* drains constitution */
# define AD_DRIN 32     /* drains intelligence (mind flayer) */
# define AD_DISE 33     /* confers diseases */
# define AD_DCAY 34     /* decays organics (brown Pudding) */
# define AD_SSEX 35     /* Succubus seduction (extended) */
# define AD_HALU 36     /* causes hallucination */
# define AD_DETH 37     /* for Death only */
# define AD_PEST 38     /* for Pestilence only */
# define AD_FAMN 39     /* for Famine only */
# define AD_SLIM 40     /* turns you into green slime */
# define AD_ENCH 41     /* remove enchantment (disenchanter) */
# define AD_CORR 42     /* corrode armor (black pudding) */
# define AD_FLPN 43     /* you feel the monster's pain -- very special-cased */
# define AD_SCLD 44     /* creates a stinking cloud */
# define AD_PITS 45     /* creates pits */
# define AD_ICEB 46     /* embeds in block of ice */
# define AD_DISP 47     /* displaces the target */
# define AD_WEBS 48     /* traps in a web; this also causes temp slowness */

# define LAST_CONTINUOUS_AD AD_WEBS

# define AD_OTHER 60    /* Numbers starting here can be used for non-damage
                         * constants stored in a damage type field, such as the
                         * field in the artilist that governs what an artifact
                         * grants when equipped, which in vanilla can only be a
                         * damage type -- resistance is granted -- but in Fourk
                         * can now also be an extrinsic.  See artifact.h */

# define AD_CLRC 240    /* random clerical spell */
# define AD_SPEL 241    /* random magic spell */
# define AD_RBRE 242    /* random breath weapon */

# define AD_SAMU 252    /* hits, may steal Amulet (Wizard) */
# define AD_CURS 253    /* random curse (ex. gremlin) */

# define LAST_AD AD_CURS

# define AD_WEBS_MAX_TURNCOUNT 150

/*
 *  Monster to monster attacks.  When a monster attacks another (mattackm),
 *  any or all of the following can be returned.  See mattackm() for more
 *  details.
 */
# define MM_MISS        0x0     /* aggressor missed */
# define MM_HIT         0x1     /* aggressor hit defender */
# define MM_DEF_DIED    0x2     /* defender died */
# define MM_AGR_DIED    0x4     /* aggressor died */

/* Return value from functions that handle attack-like actions (anything that
   can hit and damage an adjacent monster). Note that "ac_continue" varies a
   little in meaning; for a function that's checking if an attack is possible it
   means "sure, go ahead with the attack"; for a function that conditionally
   performs an attack it means "you swung your weapon past this square, and
   there weren't any monsters that got in the way". */
enum attack_check_status {
    ac_continue,        /* nothing prevents this action from happening */
    ac_cancel,          /* the attack-like action was cancelled */
    ac_somethingelse,   /* something else happened, which consumes time */
    ac_monsterhit,      /* the attack-like action hit a monster */
};

/* Argument to combat_msgc, describing what happened. */
enum combatresult {
    cr_miss,   /* an attack missed; or a passive attack hit an immunity */
    cr_hit,    /* an attack hit */
    cr_immune, /* an active attack hit, but is 100% resisted by the target */
    cr_resist, /* an attack hit but not for full effect */
    cr_kill,   /* an attack hit and killed the target, potentially petfatal */
    cr_kill0,  /* ditto, but never prints a petfatal (presumably because the
                  caller will in that case) */
};

#endif /* MONATTK_H */

