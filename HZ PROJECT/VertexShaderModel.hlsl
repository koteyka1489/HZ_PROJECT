


cbuffer cbuff
{
    matrix transform;
};



struct VS_OUT
{
    float2 tc : TEXCOORD;
    float4 pos : SV_Position;
    float4 normal : NORMAL;
};



VS_OUT main(float3 pos : POSITION, float2 tc : TEXCOORD, float3 normal : NORMAL)
{
    VS_OUT vso;
    vso.tc = tc;
    vso.pos = mul(float4(pos, 1.f), transform);
    vso.normal = normalize(mul(float4(normal, 1.f), transform));
    
    return vso;
}