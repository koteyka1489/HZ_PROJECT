
cbuffer cbuff
{
    matrix transform;
};

struct VSOut
{
    float2 tex : TEXCOORD;
    float4 pos : SV_Position;
    
};


VSOut main(float3 pos : POSITION, float2 tex : TEXCOORD)
{
    VSOut vso;
    vso.tex = tex;
    vso.pos = mul(float4(pos, 1.f), transform);
    
    return vso;
}