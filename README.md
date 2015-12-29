# VUO_NODE_Midi_Frequency_Scala

This VuoNode takes a VuoList input of values in Cents and outputs the frequencies for MIDI note numbers.

There is no need to restrain your tunings to 12 tone- this node is able to accept any number of imputs and auto-map to midi note values.  (No auto-mapping is provided- notes simply flow on from center note (currently A 69) but adding ability to change center note is trivial).

Included in this node is the ability to control pitchbend and bend-range.

For more info regarding Scala: http://www.huygens-fokker.org/scala/

And regarding the File Format: http://www.huygens-fokker.org/scala/scl_format.html

Currently the node is only able to accept VuoReal note values in Cents, however I intend to make a .scl file parser if there is interest, otherwise there are many ratio->cent converters online.

![](https://github.com/alcomposer/VUO_NODE_Midi_Frequency_Scala/blob/master/Images/ScreenShot_Scala_Node.png)
