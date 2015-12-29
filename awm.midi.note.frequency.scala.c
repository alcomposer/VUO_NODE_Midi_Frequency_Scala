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
        VuoOutputData(VuoReal) frequency,
        VuoOutputData(VuoReal) reverseDegree,
        VuoOutputData(VuoReal) pubdegree,
        VuoOutputData(VuoReal) itemsinlist,
        VuoOutputData(VuoReal) oct,
        VuoOutputData(VuoList_VuoReal) invertedTuningTable2
)
{
    // https://en.wikipedia.org/wiki/Cent_(music)

    //inspired by: https://github.com/jcpst/scl-to-frequency


    int note = noteNumber-69;


  VuoInteger tuningTableCount = VuoListGetCount_VuoReal(tuningTable);


    VuoReal degree = abs(note % tuningTableCount);
    *pubdegree = degree;
    //*reverseDegree = (tuningTableCount-1) - degree;
    *itemsinlist= tuningTableCount;

    VuoReal octave = floor(note / tuningTableCount);
    *oct = octave;

    VuoInteger notesPerOctave = tuningTableCount;

    VuoReal m = tuningTableCount;

   VuoListRemoveAll_VuoReal(*invertedTuningTable2);
   VuoReal val;

    for (unsigned long i=1; i <= tuningTableCount; i++){

        if(i != tuningTableCount){
            val= (VuoListGetValue_VuoReal(tuningTable, tuningTableCount)-(VuoListGetValue_VuoReal(tuningTable,m-1)));
            VuoListAppendValue_VuoReal(*invertedTuningTable2, val);
        }
        else {
            val = VuoListGetValue_VuoReal(tuningTable, tuningTableCount);
             VuoListAppendValue_VuoReal(*invertedTuningTable2, val);
        }

        --m;

    }



if(note >= 0 ){
    VuoReal tuning =  pow(2, VuoListGetValue_VuoReal(tuningTable, notesPerOctave) / 1200);
    VuoReal tuning2 = pow(2, VuoListGetValue_VuoReal(tuningTable, degree ) / 1200);

    *frequency = A440 * pow(tuning, ((octave * notesPerOctave) / notesPerOctave));

  if (degree > 0) *frequency *= tuning2;

}
else{

    VuoReal tuning =  pow(2, VuoListGetValue_VuoReal(*invertedTuningTable2, notesPerOctave) / 1200);
    VuoReal tuning2 = pow(2, VuoListGetValue_VuoReal(*invertedTuningTable2, degree ) / 1200);

    *frequency = A440 * pow(tuning, ((octave * notesPerOctave) / notesPerOctave));

  if (degree > 0) *frequency /= tuning2;


}

*frequency *= pow(2., ((pitchBend/8192. - 1.) * pitchBendRange)/12.);
*frequency = MAX(0.0, MIN(22050.0, *frequency));

}







