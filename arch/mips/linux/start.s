.text
.global __start
__start:
    subu $fp, $fp, $fp
    lui  $gp, %hi(_gp)
    addi $gp, %lo(_gp)
    lw   $3,  ($sp)  # argc
    addu $4,  $sp, 4 # argv
    lw   $25, %call16(main)($gp)
    and  $sp, $sp, -8
    addi $sp, $sp, -4*6
    jalr $25

    lw   $4,  stdout
    lw   $25, %call16(fflush)($gp)
    jalr $25

    lw   $25, %call16(_exit)($gp)
    jalr $25
