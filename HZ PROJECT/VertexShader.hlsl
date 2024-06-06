struct VSOut
{
    float3 color : COLOR;
    float4 pos : SV_POSITION;
};

cbuffer cbuff
{
    matrix transform;
};

VSOut main(float3 pos : POSITION, float3 color : COLOR)
{
    VSOut vso;
    vso.pos = mul(float4(pos.x, pos.y, pos.z, 1.f), transform);
    vso.color = float3(color.r, color.g, color.b);
    
    return vso;
}