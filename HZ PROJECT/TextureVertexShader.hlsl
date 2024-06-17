
cbuffer cbuff
{
    matrix transform;
};

struct VS_OUT
{
    float2 tc : TEXCOORD;
    float4 pos : SV_Position;
    
};



VS_OUT main(float3 pos : POSITION, float2 tc : TEXCOORD)
{
    VS_OUT vso;
    vso.tc = tc;
    vso.pos = mul(float4(pos, 1.f), transform);
    
    return vso;
}