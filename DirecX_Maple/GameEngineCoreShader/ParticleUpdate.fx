#include "RenderBase.fx"
#include "Function.fx"


struct ParticleShareData
{
    uint iAliveCount;
    uint iPadding0;
    uint iPadding1;
    uint iPadding2;
};

struct ParticleInfoData
{
    // 현재위치
    float4 RelativePos;
    
    // 날아가는 방향
    float4 Dir;
    
    // 죽는시간
    float MaxTime;
    
    // 현재까지 경과한 시간
    float CurTime;
    
    // 이동할때의 스피드
    float Speed;
    
    // 나 죽었다 살았다.
    uint iActive;
};

cbuffer ParticleUpdateInfo : register(b7)
{
	// 파티클이 최대 몇개까지 눈에 보일거냐?
    int ParticleMaxCount;
	// 파티클이 월드 기준으로 스폰되냐
	// 1이면 자기 위치를 가지는걸로 봅니다
    int IsWorldSpawn;
	// 원형만 지원
	// 파티클이 만들어지는 범위
    float SpawnRange;
    float MinSpeed;
    float MaxSpeed;
    float MaxLife;
    float Temp;
    float4 ObjectWorldPos; // 액터나 랜더러의 월드 포지션
};

// 그러면
RWStructuredBuffer<ParticleShareData> ParticleShareBuffer : register(u0);

// 아래 메모리는 100개 의 쓰레드에서 100개의 배열중 자기껄 알아서 압겹치게 쓸것이기 때문에 문제가 
// 문제가 없다.
RWStructuredBuffer<ParticleInfoData> ParticleInfoBuffer : register(u1);

[numthreads(128, 1, 1)]
void ParticleUpdate_CS(uint3 _id : SV_DispatchThreadID)
{
    
    if (ParticleMaxCount <= _id.x)
    {
        return;
    }
    
    // 현재 비활성화인 파티클이므로 그 파티클을 깨울지 말지를 결정해야 한다.
    if (0 == ParticleInfoBuffer[_id.x].iActive)
    {
        // 크다면 자기 자신이 깨어나야하는 녀석인지를 확인한다.
        while (0 < ParticleShareBuffer[0].iAliveCount)
        {
            int iOriginValue = ParticleShareBuffer[0].iAliveCount;
            // 나는 죽어있으니까.
            int iExchange = iOriginValue - 1;
            
            // 지원해 줍니다.
            InterlockedCompareExchange(ParticleShareBuffer[0].iAliveCount, iOriginValue, iExchange, iExchange);
            
            // 동기화된 값이 변경되지 않았다면
            if (iOriginValue == iExchange)
            {
                ParticleInfoBuffer[_id.x].iActive = 1;
                break;
            }
        }
        
        // 이녀석은 활성화 됩니다.
        if (0 != ParticleInfoBuffer[_id.x].iActive)
        {
            
        }

    }
    // 움직이는 일해야합니다
    else
    {
        
    }
        
    
    // 쓰레드를 제가 
    // SV_DispatchThreadID
    
    
    // 실제 여기서 파티클을 계산해야 겠죠.
    
    ParticleShareBuffer[0].iAliveCount = 1;
}