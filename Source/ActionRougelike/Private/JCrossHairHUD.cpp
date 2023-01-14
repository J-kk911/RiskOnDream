// Fill out your copyright notice in the Description page of Project Settings.


#include "JCrossHairHUD.h"
#include "GameFramework/HUD.h"
#include "CanvasItem.h"


AJCrossHairHUD::AJCrossHairHUD() {

}

//void AJCrossHairHUD::DrawHUD()
//{
//	Super::DrawHUD();
//
//
//	// 找到屏幕可绘区域的中心
//	FVector2D Center((Canvas->ClipX) * 0.5f, Canvas->ClipY * 0.5f);
//
//	//计算一下偏移
//	FVector2D CrosshairDrawPosition((Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5)), (Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f)));
//
//	// 画出来
//	FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
//	TileItem.BlendMode = SE_BLEND_Translucent;
//	Canvas->DrawItem(TileItem);
//
//}


