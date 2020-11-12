// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "HttpService.generated.h"

USTRUCT()
struct FRequest_Login {
	GENERATED_BODY()
		UPROPERTY() FString email;
	UPROPERTY() FString password;

	FRequest_Login() {}
};

USTRUCT()
struct FResponse_Login {
	GENERATED_BODY()
		UPROPERTY() int id;
	UPROPERTY() FString name;
	UPROPERTY() FString hash;

	FResponse_Login() {}
};

UCLASS(Blueprintable, hideCategories = (Rendering, Replication, Input, Actor, "Actor Tick"))
class THIRDPERSONMP_API AHttpService : public AActor
{
	GENERATED_BODY()
private:
	FHttpModule* Http;
	FString ApiBaseUrl = "http://localhost:5000/api/v1/";

	FString AuthorizationHeader = TEXT("Authorization");
	FString AuthorizationHash = TEXT("asdfasdf");
	void SetAuthorizationHash(FString Hash/*, TSharedRef<IHttpRequest>& Request*/);

	TSharedRef<IHttpRequest> RequestWithRoute(FString Subroute);
	void SetRequestHeaders(TSharedRef<IHttpRequest>& Request);

	TSharedRef<IHttpRequest> GetRequest(FString Subroute);
	TSharedRef<IHttpRequest> PostRequest(FString Subroute, FString ContentJsonString);
	bool Send(TSharedRef<IHttpRequest>& Request);

	bool ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful);

	template <typename StructType>
	void GetJsonStringFromStruct(StructType FilledStruct, FString& StringOutput);
	template <typename StructType>
	void GetStructFromJsonString(FHttpResponsePtr Response, StructType& StructOutput);

	void OnResponseReceived(FHttpRequestPtr RequestP, FHttpResponsePtr Response, bool bWasSuccessful);
public:
	AHttpService();
	virtual void BeginPlay() override;

	void Login(FRequest_Login LoginCredentials);
	void LoginResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void Ping();
};
