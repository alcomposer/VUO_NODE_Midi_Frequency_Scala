#include "node.h"
#include "VuoMidiNote.h"
#include "math.h"

VuoModuleMetadata({
                     "title" : "Convert Note to Frequency Scala",
                     "keywords" : [ "pitch", "synthesizer", "hertz" ],
                     "version" : "0.0.1",
                     "node": {
                                "exampleCompositions" : [ ],
                     }
                 });

void nodeEvent
(
        VuoInputData(VuoReal, {"default": 440 }) A440,
        VuoInputData(VuoList_VuoReal) tuningTable,
        VuoInputData(VuoInteger, {"default":69, "suggestedMin":0, "suggestedMax":127}) noteNumber,
        VuoInputData(VuoInteger, {"default":8192, "suggestedMin":0, "suggestedMax":16383}) pitchBend,///< Permitted values: 0 through 16383; center=8192
        VuoInputData(VuoInteger, {"default":2, "suggestedMin":0, "suggestedMax":24}) pitchBendRange,
        VuoOutputData(VuoReal) frequency

)
{
    // https://en.wikipedia.org/wiki/Cent_(music)

    //inspired by: https://github.com/jcpst/scl-to-frequency


    int note = noteNumber-69;


  VuoInteger tuningTableCount = VuoListGetCount_VuoReal(tuningTable);


    VuoReal degree = abs(note % tuningTableCount);

    VuoReal octave = floor(note / tuningTableCount);

    VuoInteger notesPerOctave = tuningTableCount;



if(note >= 0 ){
    VuoReal tuning =  pow(2, VuoListGetValue_VuoReal(tuningTable, notesPerOctave) / 1200);
    VuoReal tuning2 = pow(2, VuoListGetValue_VuoReal(tuningTable, degree ) / 1200);

    *frequency = A440 * pow(tuning, ((octave * notesPerOctave) / notesPerOctave));

  if (degree > 0) *frequency *= tuning2;

}
else{

    VuoReal tuning =  pow(2, VuoListGetValue_VuoReal(tuningTable, notesPerOctave) / 1200);
    VuoReal tuning2 = pow(2, VuoListGetValue_VuoReal(tuningTable, degree ) / 1200);

    *frequency = A440 * pow(tuning, ((octave * notesPerOctave) / notesPerOctave));

  if (degree > 0) *frequency /= tuning2;


}

*frequency *= pow(2., ((pitchBend/8192. - 1.) * pitchBendRange)/12.);
*frequency = MAX(0.0, MIN(22050.0, *frequency));

}



















