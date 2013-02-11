<?php
var $exec_string = "motionblur lenna.pgm out.pgm 0.0001 0.0001 1";
exec($exec_string);
echo (exec($exec_string));
?>