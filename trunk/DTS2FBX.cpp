/*
 * dts2fbx
 * Copyright (c) 2011 Charlie Duhor. All rights reserved.
 *
 * @DTS2FBX_LICENSE_HEADER_START@
 * 
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this software; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA, or see the FSF site: http://www.fsf.org.
 * 
 * @DTS2FBX_LICENSE_HEADER_START@
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <vector>
#include <errno.h>

#include "DTSTypes.h"
#include "DTSBase.h"
#include "DTSShape.h"

#include <fbxsdk.h>
#include <math.h>

#include <map>

class FBXExpoter
{
public:
    std::vector<KFbxSurfaceMaterial*> materials;
    
public:
    FBXExpoter();
};

FBXExpoter::FBXExpoter()
{
}

const KFbxVector4 NormalTable[] =
{
    KFbxVector4( 0.565061f, -0.270644f, -0.779396f ),
    KFbxVector4( -0.309804f, -0.731114f, 0.607860f ),
    KFbxVector4( -0.867412f, 0.472957f, 0.154619f ),
    KFbxVector4( -0.757488f, 0.498188f, -0.421925f ),
    KFbxVector4( 0.306834f, -0.915340f, 0.260778f ),
    KFbxVector4( 0.098754f, 0.639153f, -0.762713f ),
    KFbxVector4( 0.713706f, -0.558862f, -0.422252f ),
    KFbxVector4( -0.890431f, -0.407603f, -0.202466f ),
    KFbxVector4( 0.848050f, -0.487612f, -0.207475f ),
    KFbxVector4( -0.232226f, 0.776855f, 0.585293f ),
    KFbxVector4( -0.940195f, 0.304490f, -0.152706f ),
    KFbxVector4( 0.602019f, -0.491878f, -0.628991f ),
    KFbxVector4( -0.096835f, -0.494354f, -0.863850f ),
    KFbxVector4( 0.026630f, -0.323659f, -0.945799f ),
    KFbxVector4( 0.019208f, 0.909386f, 0.415510f ),
    KFbxVector4( 0.854440f, 0.491730f, 0.167731f ),
    KFbxVector4( -0.418835f, 0.866521f, -0.271512f ),
    KFbxVector4( 0.465024f, 0.409667f, 0.784809f ),
    KFbxVector4( -0.674391f, -0.691087f, -0.259992f ),
    KFbxVector4( 0.303858f, -0.869270f, -0.389922f ),
    KFbxVector4( 0.991333f, 0.090061f, -0.095640f ),
    KFbxVector4( -0.275924f, -0.369550f, 0.887298f ),
    KFbxVector4( 0.426545f, -0.465962f, 0.775202f ),
    KFbxVector4( -0.482741f, -0.873278f, -0.065920f ),
    KFbxVector4( 0.063616f, 0.932012f, -0.356800f ),
    KFbxVector4( 0.624786f, -0.061315f, 0.778385f ),
    KFbxVector4( -0.530300f, 0.416850f, 0.738253f ),
    KFbxVector4( 0.312144f, -0.757028f, -0.573999f ),
    KFbxVector4( 0.399288f, -0.587091f, -0.704197f ),
    KFbxVector4( -0.132698f, 0.482877f, 0.865576f ),
    KFbxVector4( 0.950966f, 0.306530f, 0.041268f ),
    KFbxVector4( -0.015923f, -0.144300f, 0.989406f ),
    KFbxVector4( -0.407522f, -0.854193f, 0.322925f ),
    KFbxVector4( -0.932398f, 0.220464f, 0.286408f ),
    KFbxVector4( 0.477509f, 0.876580f, 0.059936f ),
    KFbxVector4( 0.337133f, 0.932606f, -0.128796f ),
    KFbxVector4( -0.638117f, 0.199338f, 0.743687f ),
    KFbxVector4( -0.677454f, 0.445349f, 0.585423f ),
    KFbxVector4( -0.446715f, 0.889059f, -0.100099f ),
    KFbxVector4( -0.410024f, 0.909168f, 0.072759f ),
    KFbxVector4( 0.708462f, 0.702103f, -0.071641f ),
    KFbxVector4( -0.048801f, -0.903683f, -0.425411f ),
    KFbxVector4( -0.513681f, -0.646901f, 0.563606f ),
    KFbxVector4( -0.080022f, 0.000676f, -0.996793f ),
    KFbxVector4( 0.066966f, -0.991150f, -0.114615f ),
    KFbxVector4( -0.245220f, 0.639318f, -0.728793f ),
    KFbxVector4( 0.250978f, 0.855979f, 0.452006f ),
    KFbxVector4( -0.123547f, 0.982443f, -0.139791f ),
    KFbxVector4( -0.794825f, 0.030254f, -0.606084f ),
    KFbxVector4( -0.772905f, 0.547941f, 0.319967f ),
    KFbxVector4( 0.916347f, 0.369614f, -0.153928f ),
    KFbxVector4( -0.388203f, 0.105395f, 0.915527f ),
    KFbxVector4( -0.700468f, -0.709334f, 0.078677f ),
    KFbxVector4( -0.816193f, 0.390455f, 0.425880f ),
    KFbxVector4( -0.043007f, 0.769222f, -0.637533f ),
    KFbxVector4( 0.911444f, 0.113150f, 0.395560f ),
    KFbxVector4( 0.845801f, 0.156091f, -0.510153f ),
    KFbxVector4( 0.829801f, -0.029340f, 0.557287f ),
    KFbxVector4( 0.259529f, 0.416263f, 0.871418f ),
    KFbxVector4( 0.231128f, -0.845982f, 0.480515f ),
    KFbxVector4( -0.626203f, -0.646168f, 0.436277f ),
    KFbxVector4( -0.197047f, -0.065791f, 0.978184f ),
    KFbxVector4( -0.255692f, -0.637488f, -0.726794f ),
    KFbxVector4( 0.530662f, -0.844385f, -0.073567f ),
    KFbxVector4( -0.779887f, 0.617067f, -0.104899f ),
    KFbxVector4( 0.739908f, 0.113984f, 0.662982f ),
    KFbxVector4( -0.218801f, 0.930194f, -0.294729f ),
    KFbxVector4( -0.374231f, 0.818666f, 0.435589f ),
    KFbxVector4( -0.720250f, -0.028285f, 0.693137f ),
    KFbxVector4( 0.075389f, 0.415049f, 0.906670f ),
    KFbxVector4( -0.539724f, -0.106620f, 0.835063f ),
    KFbxVector4( -0.452612f, -0.754669f, -0.474991f ),
    KFbxVector4( 0.682822f, 0.581234f, -0.442629f ),
    KFbxVector4( 0.002435f, -0.618462f, -0.785811f ),
    KFbxVector4( -0.397631f, 0.110766f, -0.910835f ),
    KFbxVector4( 0.133935f, -0.985438f, 0.104754f ),
    KFbxVector4( 0.759098f, -0.608004f, 0.232595f ),
    KFbxVector4( -0.825239f, -0.256087f, 0.503388f ),
    KFbxVector4( 0.101693f, -0.565568f, 0.818408f ),
    KFbxVector4( 0.386377f, 0.793546f, -0.470104f ),
    KFbxVector4( -0.520516f, -0.840690f, 0.149346f ),
    KFbxVector4( -0.784549f, -0.479672f, 0.392935f ),
    KFbxVector4( -0.325322f, -0.927581f, -0.183735f ),
    KFbxVector4( -0.069294f, -0.428541f, 0.900861f ),
    KFbxVector4( 0.993354f, -0.115023f, -0.004288f ),
    KFbxVector4( -0.123896f, -0.700568f, 0.702747f ),
    KFbxVector4( -0.438031f, -0.120880f, -0.890795f ),
    KFbxVector4( 0.063314f, 0.813233f, 0.578484f ),
    KFbxVector4( 0.322045f, 0.889086f, -0.325289f ),
    KFbxVector4( -0.133521f, 0.875063f, -0.465228f ),
    KFbxVector4( 0.637155f, 0.564814f, 0.524422f ),
    KFbxVector4( 0.260092f, -0.669353f, 0.695930f ),
    KFbxVector4( 0.953195f, 0.040485f, -0.299634f ),
    KFbxVector4( -0.840665f, -0.076509f, 0.536124f ),
    KFbxVector4( -0.971350f, 0.202093f, 0.125047f ),
    KFbxVector4( -0.804307f, -0.396312f, -0.442749f ),
    KFbxVector4( -0.936746f, 0.069572f, 0.343027f ),
    KFbxVector4( 0.426545f, -0.465962f, 0.775202f ),
    KFbxVector4( 0.794542f, -0.227450f, 0.563000f ),
    KFbxVector4( -0.892172f, 0.091169f, -0.442399f ),
    KFbxVector4( -0.312654f, 0.541264f, 0.780564f ),
    KFbxVector4( 0.590603f, -0.735618f, -0.331743f ),
    KFbxVector4( -0.098040f, -0.986713f, 0.129558f ),
    KFbxVector4( 0.569646f, 0.283078f, -0.771603f ),
    KFbxVector4( 0.431051f, -0.407385f, -0.805129f ),
    KFbxVector4( -0.162087f, -0.938749f, -0.304104f ),
    KFbxVector4( 0.241533f, -0.359509f, 0.901341f ),
    KFbxVector4( -0.576191f, 0.614939f, 0.538380f ),
    KFbxVector4( -0.025110f, 0.085740f, 0.996001f ),
    KFbxVector4( -0.352693f, -0.198168f, 0.914515f ),
    KFbxVector4( -0.604577f, 0.700711f, 0.378802f ),
    KFbxVector4( 0.465024f, 0.409667f, 0.784809f ),
    KFbxVector4( -0.254684f, -0.030474f, -0.966544f ),
    KFbxVector4( -0.604789f, 0.791809f, 0.085259f ),
    KFbxVector4( -0.705147f, -0.399298f, 0.585943f ),
    KFbxVector4( 0.185691f, 0.017236f, -0.982457f ),
    KFbxVector4( 0.044588f, 0.973094f, 0.226052f ),
    KFbxVector4( -0.405463f, 0.642367f, 0.650357f ),
    KFbxVector4( -0.563959f, 0.599136f, -0.568319f ),
    KFbxVector4( 0.367162f, -0.072253f, -0.927347f ),
    KFbxVector4( 0.960429f, -0.213570f, -0.178783f ),
    KFbxVector4( -0.192629f, 0.906005f, 0.376893f ),
    KFbxVector4( -0.199718f, -0.359865f, -0.911378f ),
    KFbxVector4( 0.485072f, 0.121233f, -0.866030f ),
    KFbxVector4( 0.467163f, -0.874294f, 0.131792f ),
    KFbxVector4( -0.638953f, -0.716603f, 0.279677f ),
    KFbxVector4( -0.622710f, 0.047813f, -0.780990f ),
    KFbxVector4( 0.828724f, -0.054433f, -0.557004f ),
    KFbxVector4( 0.130241f, 0.991080f, 0.028245f ),
    KFbxVector4( 0.310995f, -0.950076f, -0.025242f ),
    KFbxVector4( 0.818118f, 0.275336f, 0.504850f ),
    KFbxVector4( 0.676328f, 0.387023f, 0.626733f ),
    KFbxVector4( -0.100433f, 0.495114f, -0.863004f ),
    KFbxVector4( -0.949609f, -0.240681f, -0.200786f ),
    KFbxVector4( -0.102610f, 0.261831f, -0.959644f ),
    KFbxVector4( -0.845732f, -0.493136f, 0.203850f ),
    KFbxVector4( 0.672617f, -0.738838f, 0.041290f ),
    KFbxVector4( 0.380465f, 0.875938f, 0.296613f ),
    KFbxVector4( -0.811223f, 0.262027f, -0.522742f ),
    KFbxVector4( -0.074423f, -0.775670f, -0.626736f ),
    KFbxVector4( -0.286499f, 0.755850f, -0.588735f ),
    KFbxVector4( 0.291182f, -0.276189f, -0.915933f ),
    KFbxVector4( -0.638117f, 0.199338f, 0.743687f ),
    KFbxVector4( 0.439922f, -0.864433f, -0.243359f ),
    KFbxVector4( 0.177649f, 0.206919f, 0.962094f ),
    KFbxVector4( 0.277107f, 0.948521f, 0.153361f ),
    KFbxVector4( 0.507629f, 0.661918f, -0.551523f ),
    KFbxVector4( -0.503110f, -0.579308f, -0.641313f ),
    KFbxVector4( 0.600522f, 0.736495f, -0.311364f ),
    KFbxVector4( -0.691096f, -0.715301f, -0.103592f ),
    KFbxVector4( -0.041083f, -0.858497f, 0.511171f ),
    KFbxVector4( 0.207773f, -0.480062f, -0.852274f ),
    KFbxVector4( 0.795719f, 0.464614f, 0.388543f ),
    KFbxVector4( -0.100433f, 0.495114f, -0.863004f ),
    KFbxVector4( 0.703249f, 0.065157f, -0.707951f ),
    KFbxVector4( -0.324171f, -0.941112f, 0.096024f ),
    KFbxVector4( -0.134933f, -0.940212f, 0.312722f ),
    KFbxVector4( -0.438240f, 0.752088f, -0.492249f ),
    KFbxVector4( 0.964762f, -0.198855f, 0.172311f ),
    KFbxVector4( -0.831799f, 0.196807f, 0.519015f ),
    KFbxVector4( -0.508008f, 0.819902f, 0.263986f ),
    KFbxVector4( 0.471075f, -0.001146f, 0.882092f ),
    KFbxVector4( 0.919512f, 0.246162f, -0.306435f ),
    KFbxVector4( -0.960050f, 0.279828f, -0.001187f ),
    KFbxVector4( 0.110232f, -0.847535f, -0.519165f ),
    KFbxVector4( 0.208229f, 0.697360f, 0.685806f ),
    KFbxVector4( -0.199680f, -0.560621f, 0.803637f ),
    KFbxVector4( 0.170135f, -0.679985f, -0.713214f ),
    KFbxVector4( 0.758371f, -0.494907f, 0.424195f ),
    KFbxVector4( 0.077734f, -0.755978f, 0.649965f ),
    KFbxVector4( 0.612831f, -0.672475f, 0.414987f ),
    KFbxVector4( 0.142776f, 0.836698f, -0.528726f ),
    KFbxVector4( -0.765185f, 0.635778f, 0.101382f ),
    KFbxVector4( 0.669873f, -0.419737f, 0.612447f ),
    KFbxVector4( 0.593549f, 0.194879f, 0.780847f ),
    KFbxVector4( 0.646930f, 0.752173f, 0.125368f ),
    KFbxVector4( 0.837721f, 0.545266f, -0.030127f ),
    KFbxVector4( 0.541505f, 0.768070f, 0.341820f ),
    KFbxVector4( 0.760679f, -0.365715f, -0.536301f ),
    KFbxVector4( 0.381516f, 0.640377f, 0.666605f ),
    KFbxVector4( 0.565794f, -0.072415f, -0.821361f ),
    KFbxVector4( -0.466072f, -0.401588f, 0.788356f ),
    KFbxVector4( 0.987146f, 0.096290f, 0.127560f ),
    KFbxVector4( 0.509709f, -0.688886f, -0.515396f ),
    KFbxVector4( -0.135132f, -0.988046f, -0.074192f ),
    KFbxVector4( 0.600499f, 0.476471f, -0.642166f ),
    KFbxVector4( -0.732326f, -0.275320f, -0.622815f ),
    KFbxVector4( -0.881141f, -0.470404f, 0.048078f ),
    KFbxVector4( 0.051548f, 0.601042f, 0.797553f ),
    KFbxVector4( 0.402027f, -0.763183f, 0.505891f ),
    KFbxVector4( 0.404233f, -0.208288f, 0.890624f ),
    KFbxVector4( -0.311793f, 0.343843f, 0.885752f ),
    KFbxVector4( 0.098132f, -0.937014f, 0.335223f ),
    KFbxVector4( 0.537158f, 0.830585f, -0.146936f ),
    KFbxVector4( 0.725277f, 0.298172f, -0.620538f ),
    KFbxVector4( -0.882025f, 0.342976f, -0.323110f ),
    KFbxVector4( -0.668829f, 0.424296f, -0.610443f ),
    KFbxVector4( -0.408835f, -0.476442f, -0.778368f ),
    KFbxVector4( 0.809472f, 0.397249f, -0.432375f ),
    KFbxVector4( -0.909184f, -0.205938f, -0.361903f ),
    KFbxVector4( 0.866930f, -0.347934f, -0.356895f ),
    KFbxVector4( 0.911660f, -0.141281f, -0.385897f ),
    KFbxVector4( -0.431404f, -0.844074f, -0.318480f ),
    KFbxVector4( -0.950593f, -0.073496f, 0.301614f ),
    KFbxVector4( -0.719716f, 0.626915f, -0.298305f ),
    KFbxVector4( -0.779887f, 0.617067f, -0.104899f ),
    KFbxVector4( -0.475899f, -0.542630f, 0.692151f ),
    KFbxVector4( 0.081952f, -0.157248f, -0.984153f ),
    KFbxVector4( 0.923990f, -0.381662f, -0.024025f ),
    KFbxVector4( -0.957998f, 0.120979f, -0.260008f ),
    KFbxVector4( 0.306601f, 0.227975f, -0.924134f ),
    KFbxVector4( -0.141244f, 0.989182f, 0.039601f ),
    KFbxVector4( 0.077097f, 0.186288f, -0.979466f ),
    KFbxVector4( -0.630407f, -0.259801f, 0.731499f ),
    KFbxVector4( 0.718150f, 0.637408f, 0.279233f ),
    KFbxVector4( 0.340946f, 0.110494f, 0.933567f ),
    KFbxVector4( -0.396671f, 0.503020f, -0.767869f ),
    KFbxVector4( 0.636943f, -0.245005f, 0.730942f ),
    KFbxVector4( -0.849605f, -0.518660f, -0.095724f ),
    KFbxVector4( -0.388203f, 0.105395f, 0.915527f ),
    KFbxVector4( -0.280671f, -0.776541f, -0.564099f ),
    KFbxVector4( -0.601680f, 0.215451f, -0.769131f ),
    KFbxVector4( -0.660112f, -0.632371f, -0.405412f ),
    KFbxVector4( 0.921096f, 0.284072f, 0.266242f ),
    KFbxVector4( 0.074850f, -0.300846f, 0.950731f ),
    KFbxVector4( 0.943952f, -0.067062f, 0.323198f ),
    KFbxVector4( -0.917838f, -0.254589f, 0.304561f ),
    KFbxVector4( 0.889843f, -0.409008f, 0.202219f ),
    KFbxVector4( -0.565849f, 0.753721f, -0.334246f ),
    KFbxVector4( 0.791460f, 0.555918f, -0.254060f ),
    KFbxVector4( 0.261936f, 0.703590f, -0.660568f ),
    KFbxVector4( -0.234406f, 0.952084f, 0.196444f ),
    KFbxVector4( 0.111205f, 0.979492f, -0.168014f ),
    KFbxVector4( -0.869844f, -0.109095f, -0.481113f ),
    KFbxVector4( -0.337728f, -0.269701f, -0.901777f ),
    KFbxVector4( 0.366793f, 0.408875f, -0.835634f ),
    KFbxVector4( -0.098749f, 0.261316f, 0.960189f ),
    KFbxVector4( -0.272379f, -0.847100f, 0.456324f ),
    KFbxVector4( -0.319506f, 0.287444f, -0.902935f ),
    KFbxVector4( 0.873383f, -0.294109f, 0.388203f ),
    KFbxVector4( -0.088950f, 0.710450f, 0.698104f ),
    KFbxVector4( 0.551238f, -0.786552f, 0.278340f ),
    KFbxVector4( 0.724436f, -0.663575f, -0.186712f ),
    KFbxVector4( 0.529741f, -0.606539f, 0.592861f ),
    KFbxVector4( -0.949743f, -0.282514f, 0.134809f ),
    KFbxVector4( 0.155047f, 0.419442f, -0.894443f ),
    KFbxVector4( -0.562653f, -0.329139f, -0.758346f ),
    KFbxVector4( 0.816407f, -0.576953f, 0.024576f ),
    KFbxVector4( 0.178550f, -0.950242f, -0.255266f ),
    KFbxVector4( 0.479571f, 0.706691f, 0.520192f ),
    KFbxVector4( 0.391687f, 0.559884f, -0.730145f ),
    KFbxVector4( 0.724872f, -0.205570f, -0.657496f ),
    KFbxVector4( -0.663196f, -0.517587f, -0.540624f ),
    KFbxVector4( -0.660054f, -0.122486f, -0.741165f ),
    KFbxVector4( -0.531989f, 0.374711f, -0.759328f ),
    KFbxVector4( 0.194979f, -0.059120f, 0.979024f )
};

int ExportFBX(KFbxSdkManager* sdkManager, KFbxScene* scene, const char* fbxFile)
{
	KFbxExporter*   exporter   = KFbxExporter::Create(sdkManager, "");
	KFbxIOSettings* ioSettings = KFbxIOSettings::Create(sdkManager, IOSROOT);

	ioSettings->SetBoolProp(EXP_FBX_MATERIAL,  true);
	ioSettings->SetBoolProp(EXP_FBX_TEXTURE,   true);
	ioSettings->SetBoolProp(EXP_FBX_EMBEDDED,  true);
	ioSettings->SetBoolProp(EXP_FBX_ANIMATION, true);
	ioSettings->SetBoolProp(EXP_FBX_SHAPE,     true);

	if (!exporter->Initialize(fbxFile, -1, ioSettings))
	{
		fprintf(stderr, "Failed to initialize FBX exporter\n");
		exporter->Destroy();
		return -1;
	}

	if (!exporter->Export(scene))
	{
		fprintf(stderr, "Failed to produce FBX file\n");
		exporter->Destroy();
		return -1;
	}

	exporter->Destroy();
	return 0;
}

KFbxTexture* createTexture(KFbxSdkManager* pSdkManager, const char* name)
{
    KFbxFileTexture* texture = KFbxFileTexture::Create(pSdkManager,"");
    
    // Set texture properties.
    texture->SetFileName    (name);
    texture->SetName        ("Diffuse Texture");
    texture->SetTextureUse  (KFbxTexture::eSTANDARD);
    texture->SetMappingType (KFbxTexture::eUV);
    texture->SetMaterialUse (KFbxFileTexture::eMODEL_MATERIAL);
    texture->SetSwapUV      (false);
    texture->SetAlphaSource (KFbxTexture::eNONE);
    texture->SetTranslation (0.0, 0.0);
    texture->SetScale       (1.0, 1.0);
    texture->SetRotation    (0.0, 0.0);
    return texture;
}

KFbxSurfaceMaterial* convertMaterial(const DTSResolver& resolver, const DTSShape& shape, const DTSMaterial& material, KFbxSdkManager* sdkManager, KFbxScene* scene)
{
    std::string name(material.name);
    size_t      lastDot = name.rfind(".");

    if (lastDot != std::string::npos)
    {
        name = name.substr(0, lastDot);
    }
    
    std::string path = resolver.resolve(material.name);
    
    KFbxSurfacePhong* materialFbx = KFbxSurfacePhong::Create(sdkManager, name.c_str());
 
    materialFbx->Diffuse.ConnectSrcObject(createTexture(sdkManager, path.c_str()));
    return materialFbx;
} 

KFbxVector4 DTSQuaternionToEuler(const Quaternion& q)
{
    Quaternion q1(q);
    
    q1.w = -q1.w;
    
    double sqw  = q1.w * q1.w;
    double sqx  = q1.x * q1.x;
    double sqy  = q1.y * q1.y;
    double sqz  = q1.z * q1.z;
    double test = q1.x * q1.y + q1.z * q1.w;
    double unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
    
    double heading, attitude, bank;
    
    if (test > 0.49999 * unit)
    {
        // singularity at north pole
        heading  = 2 * atan2(q1.x, q1.w);
        attitude = M_PI/2;
        bank     = 0;
    }
    else if (test < -0.49999*unit)
    {
        // singularity at south pole
        heading  = -2 * atan2(q1.x, q1.w);
        attitude = -M_PI / 2;
        bank     = 0;
    }
    else
    {
        double headingA = 2 * q1.y * q1.w - 2 * q1.x * q1.z;
        double headingB = sqx - sqy - sqz + sqw;
        
        double bankA = 2 * q1.x * q1.w - 2 * q1.y * q1.z;
        double bankB = -sqx + sqy - sqz + sqw;
        
        heading  = atan2(headingB, headingA);
        bank     = atan2(bankB,    bankA);
        attitude = asin (2 * test / unit);
    }
    
    heading  *= (180 / M_PI);
    bank     *= (180 / M_PI);
    attitude *= (180 / M_PI);
    return KFbxVector4(-bank, attitude, heading - 90);
}

void convertMesh(FBXExpoter& exporter, const DTSBase& shape, const DTSMesh& mesh, KFbxSdkManager* sdkManager, KFbxScene* scene, KFbxNode* node)
{
    if (mesh.vertsPerFrame == 0)
    {
        return;
    }

    std::string meshName;

//#define __DEBUG__
    
    int                          index;
    KFbxMesh*                    meshFbx       = KFbxMesh::Create(node, node->GetName());
    KFbxGeometryElementUV*       meshUVs       = meshFbx->CreateElementUV("uv");
    KFbxGeometryElementNormal*   meshNormals   = meshFbx->CreateElementNormal();
    KFbxGeometryElementMaterial* meshMaterials = meshFbx->CreateElementMaterial();
    
    meshMaterials->SetMappingMode  (KFbxGeometryElement::eBY_POLYGON);
    meshMaterials->SetReferenceMode(KFbxGeometryElement::eINDEX_TO_DIRECT);
    meshMaterials->GetIndexArray().Add(0);
    
    meshFbx->InitControlPoints(mesh.vertsPerFrame);
    meshUVs->SetMappingMode  (KFbxGeometryElementUV::eBY_CONTROL_POINT);
    meshUVs->SetReferenceMode(KFbxGeometryElementUV::eDIRECT);
    meshNormals->SetMappingMode  (KFbxGeometryElement::eBY_CONTROL_POINT);
    meshNormals->SetReferenceMode(KFbxGeometryElement::eDIRECT);
    
    KFbxVector4* meshVectors = meshFbx->GetControlPoints();
    
    for (index = 0; index < mesh.vertsPerFrame; index++)
    {
        meshVectors[index].Set(mesh.verts[index].x, mesh.verts[index].y, mesh.verts[index].z);
        meshUVs->GetDirectArray().Add(KFbxVector2(mesh.tverts[index].x, 1.0 - mesh.tverts[index].y));

#ifdef __DEBUG__
        fprintf(stderr, "%f %f %f %f %f\n", mesh.verts[index].x, mesh.verts[index].y, mesh.verts[index].z, mesh.tverts[index].x, mesh.tverts[index].y);
#endif
    }
    
    if (mesh.enormals.size() > 0)
    {
        for (index = 0; index < mesh.vertsPerFrame; index++)
        {
            meshNormals->GetDirectArray().Add(NormalTable[mesh.enormals[index]]);
        }
    }
    else
    {
        for (index = 0; index < mesh.vertsPerFrame; index++)
        {
            KFbxVector4 n(mesh.normals[index].x, mesh.normals[index].y, mesh.normals[index].z);
            
            meshNormals->GetDirectArray().Add(n);
        }
    }
    
    std::vector<DTSPrimitive>::const_iterator primIt, primEnd(mesh.primitives.end());
    std::map<int,int> materialMap;
    bool              orient;
    
    for (primIt = mesh.primitives.begin(); primIt != primEnd; ++primIt)
    {
        const DTSPrimitive& primitive(*primIt);
        int mapMatIndex = -1;
        int rawMatIndex = primitive.type & 0xffff;
        
        std::map<int,int>::const_iterator matIt = materialMap.find(rawMatIndex);
        
        if (matIt == materialMap.end())
        {
            mapMatIndex = node->AddMaterial(exporter.materials[rawMatIndex]);
            materialMap.insert(std::pair<int,int>(rawMatIndex, mapMatIndex));
        }
        else
        {
            mapMatIndex = matIt->second;
        }
        
        switch (primitive.type >> 30)
        {
            case 0: // TRIANGLE_LIST:
                for (index = primitive.firstElement; index < (primitive.firstElement + primitive.numElements); index += 3)
                {
                    meshFbx->BeginPolygon(mapMatIndex);
                    meshFbx->AddPolygon(mesh.indices[index]);
                    meshFbx->AddPolygon(mesh.indices[index + 1]);
                    meshFbx->AddPolygon(mesh.indices[index + 2]);
                    meshFbx->EndPolygon();
                }
                break;
            case 1: // TRIANGLE_STRIP:
                for (index = primitive.firstElement + 2, orient = true; index < (primitive.firstElement + primitive.numElements); index++, orient = !orient)
                {  
                    meshFbx->BeginPolygon(mapMatIndex);
                    
                    if (orient)
                    {
                        meshFbx->AddPolygon(mesh.indices[index - 0]);
                        meshFbx->AddPolygon(mesh.indices[index - 1]);
                        meshFbx->AddPolygon(mesh.indices[index - 2]);
                    }
                    else
                    {
                        meshFbx->AddPolygon(mesh.indices[index - 0]);
                        meshFbx->AddPolygon(mesh.indices[index - 2]);
                        meshFbx->AddPolygon(mesh.indices[index - 1]);
                    }
                    
                    meshFbx->EndPolygon();
                }
                break;
            case 2: // TRIANGLE_FAN:
                for (index = primitive.firstElement + 2; index < (primitive.firstElement + primitive.numElements); index++)
                {
                    meshFbx->BeginPolygon(mapMatIndex);
                    meshFbx->AddPolygon(mesh.indices[primitive.firstElement]);
                    meshFbx->AddPolygon(mesh.indices[index - 1]);
                    meshFbx->AddPolygon(mesh.indices[index - 0]);
                    meshFbx->EndPolygon();
                }
                break;
            default:
                assert(false);
                break;
        }
    }
    
#ifdef __DEBUG__
    fprintf(stderr, "*****\n");
#endif
    
    node->SetNodeAttribute(meshFbx);
    node->SetShadingMode(KFbxNode::eTEXTURE_SHADING);
}

void convertNodePositionAndRotation(const DTSShape& shape, int nodeIndex, KFbxNode* node)
{
    if (nodeIndex != -1)
    {
        KFbxVector4 translation;
        KFbxVector4 rotation;
    
        translation = KFbxVector4(
                              shape.nodeDefTranslations[nodeIndex].x,
                              shape.nodeDefTranslations[nodeIndex].z - 0.5,
                              -shape.nodeDefTranslations[nodeIndex].y);
    
        rotation = DTSQuaternionToEuler(shape.nodeDefRotations[nodeIndex]);
    
        node->LclTranslation.Set(translation);
        node->LclRotation.Set(rotation);
    }
    else
    {
        Quaternion q;
        q.x = 0.707083; q.y = 0.000000; q.z = 0.000000; q.w = -0.707083;
        //q.x = 0; q.y = 0; q.z = 0; q.w = 0;
        
        node->LclTranslation.Set(KFbxVector4(-1, -0.5, 0));
        node->LclRotation.Set(KFbxVector4(0, 90, 0));
    }
}

int convertObject(FBXExpoter& exporter, const DTSShape& shape, const DTSSubshape& subshape, const DTSObject& object, KFbxSdkManager* sdkManager, KFbxScene* scene, KFbxNode* parentNode)
{
    int meshIndex;
    
    for (meshIndex = object.firstMesh; meshIndex < (object.firstMesh + object.numMeshes); meshIndex++)
    {
        std::string nodeName;
        
        if (object.name != -1)
        {
            nodeName = shape.names[object.name];
        }

        if (strncasecmp(nodeName.c_str(), "col", 3) == 0)
        {
            // Skip collisions
            continue;
        }

        KFbxNode* node = KFbxNode::Create(sdkManager, nodeName.c_str());

        convertMesh(exporter, shape, shape.meshes[meshIndex], sdkManager, scene, node);
        convertNodePositionAndRotation(shape, object.node, node);
        parentNode->AddChild(node);
    }
    
    return 0;
}

int convertSubshape(FBXExpoter& exporter, const DTSShape& shape, const DTSSubshape& subshape, KFbxSdkManager* sdkManager, KFbxScene* scene, KFbxNode* parentNode)
{
    int objectIndex;
    
    for (objectIndex = subshape.firstObject; objectIndex < (subshape.firstObject + subshape.numObjects); objectIndex++)
    {
        convertObject(exporter, shape, subshape, shape.objects[objectIndex], sdkManager, scene, parentNode);
    }
    
    return 0;
}

int convertSkeleton(FBXExpoter exporter, const DTSShape& shape, KFbxSdkManager* sdkManager, KFbxScene* scene)
{
    std::vector<DTSNode>::const_iterator nodeIt, nodeEnd(shape.nodes.end());
    std::vector<KFbxNode*>     nodes;
    std::vector<KFbxSkeleton*> skeletons;
    int index;
    
    for (nodeIt = shape.nodes.begin(), index = 0; nodeIt != nodeEnd; ++nodeIt, ++index)
    {
        const DTSNode& node(*nodeIt);
        std::string    nodeName;
        
        if (node.name != -1)
        {
            nodeName = shape.names[node.name];
        }
        
        KFbxNode*     currentNode     = KFbxNode::Create(scene, nodeName.c_str());
        KFbxSkeleton* currentSkeleton = KFbxSkeleton::Create(scene, nodeName.c_str());
        
        convertNodePositionAndRotation(shape, index, currentNode);
        currentNode->SetNodeAttribute(currentSkeleton);
        
        nodes.push_back    (currentNode);
        skeletons.push_back(currentSkeleton);
    }

    for (nodeIt = shape.nodes.begin(), index = 0; nodeIt != nodeEnd; ++nodeIt, ++index)
    {
        const DTSNode& node(*nodeIt);
        
        if (node.parent != -1)
        {
            nodes[node.parent]->AddChild(nodes[index]);
        }
        else
        {
            scene->GetRootNode()->AddChild(nodes[index]);
        }
    }

    return 0;
}

int convert(const DTSResolver& resolver, const DTSShape& shape, const char* fbxFile)
{
    FBXExpoter      exporter;
	KFbxSdkManager* sdkManager = KFbxSdkManager::Create();
	KFbxScene*      scene      = KFbxScene::Create(sdkManager, "");
    KFbxNode*       rootNode   = scene->GetRootNode();
    int             index;
    
    {
        std::vector<DTSMaterial>::const_iterator matIt, matEnd(shape.materials.end());
        
        for (matIt = shape.materials.begin(); matIt != matEnd; ++matIt)
        {
            exporter.materials.push_back(convertMaterial(resolver, shape, *matIt, sdkManager, scene));
        }
    }
    
    {
        bool hasSkin = false;
        
        std::vector<DTSMesh>::const_iterator meshIt, meshEnd(shape.meshes.end());
        
        for (meshIt = shape.meshes.begin(); meshIt != meshEnd; ++meshIt)
        {
            if (meshIt->type == DTSMesh::T_Skin)
            {
                hasSkin = true;
            }
        }
        
        if (hasSkin)
        {
            convertSkeleton(exporter, shape, sdkManager, scene);
        }
    }
    
    if (shape.subshapes.size() == 1)
    {
        convertSubshape(exporter, shape, shape.subshapes[0], sdkManager, scene, rootNode);
    }
    else
    {
        std::vector<DTSSubshape>::const_iterator subshapeIt, subshapeEnd(shape.subshapes.end());
        
        for (subshapeIt = shape.subshapes.begin(), index = 0; subshapeIt != subshapeEnd; ++subshapeIt, ++index)
        {
            char subshapeName[64];
            
            sprintf(subshapeName, "Subshape %i", index);
            
            KFbxNode* subshapeNode = KFbxNode::Create(rootNode, subshapeName);
            
            convertSubshape(exporter, shape, *subshapeIt, sdkManager, scene, subshapeNode);
            rootNode->AddChild(subshapeNode);
        }
    }
    
    return ExportFBX(sdkManager, scene, fbxFile);
}
