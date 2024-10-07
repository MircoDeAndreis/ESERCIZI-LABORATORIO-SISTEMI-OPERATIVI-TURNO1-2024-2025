#include <stdio.h>
#include "cifrario_di_Cesare.h"

int main() {
    char encoded[] = "Kn\"eqtuq\"hqtpkueg\"wp)kpvtqfw|kqpg\"cn\"nkpiwciikq\"fk\"rtqitcooc|kqpg\"E\"g\"cnnc\"rtqitcooc|kqpg\"korgtcvkxc0\"Wp\"pwogtq\"eqpukuvgpvg\"fk\"qtg\"gb\"wvknk||cvq\"rgt\"uxqnigtg\"gugtekvc|kqpk\"kp\"ncdqtcvqtkq\"hkpcnk||cvg\"c\"rtgpfgtg\"eqphkfgp|c\"eqp\"kn\"nkpiwciikq\"vtcokvg\"nc\"tgcnk||c|kqpg\"fk\"rtqitcook\"kp\"nkpiwciikq\"E0";
    decoder(encoded);
    printf("%s",encoded);
    return 0;
}