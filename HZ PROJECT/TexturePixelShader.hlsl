Texture2D tex;
SamplerState smpState;



float4 main(float2 tc : TEXCOORD) : SV_TARGET
{
    return tex.Sample(smpState, tc);
}