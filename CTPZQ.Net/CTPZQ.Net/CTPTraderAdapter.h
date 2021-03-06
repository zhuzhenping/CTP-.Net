﻿/////////////////////////////////////////////////////////////////////////
/// CTP证券 C++ => .Net Framework Adapter
/// Author:	shawn666.liu@hotmail.com
/// Date: 20140906
/////////////////////////////////////////////////////////////////////////
#pragma once

#include "ThostFtdcTraderApiSSE.h"
#include "Delegates.h"

namespace Native{
	class CTraderSpi;
}

namespace CTPZQ
{
	using namespace Native;

	public ref class CTPTraderAdapter
	{
	public:
		/// <summary>
		///创建CTPTraderAdapter
		///存贮订阅信息文件的目录，默认为当前目录
		/// </summary>
		CTPTraderAdapter();
		/// <summary>
		///创建CTPTraderAdapter
		/// </summary>
		/// <param name="pszFlowPath">存贮订阅信息文件的目录</param>
		CTPTraderAdapter(String^ pszFlowPath);

		~CTPTraderAdapter();

		/// <summary>
		/// 获取对应的CTP官方C++库的版本发布日期，如20140811等
		/// </summary>
		String^ GetCtpVersionDate();

	private:
		CtpErrRtnEventHandler^ CtpErrRtn_delegate;
		CtpFrontEventHandler^ CtpFront_delegate;
		CtpRspEventHandler^ CtpRsp_delegate;
		CtpRspQryEventHandler^ CtpRspQry_delegate;
		CtpRtnEventHandler^ CtpRtn_delegate;

		CZQThostFtdcTraderApi* m_pApi;
		CTraderSpi* m_pSpi;
	
		// events
	public:
		/// <summary>
		/// 处理所有的OnFront****回调事件
		/// </summary>
		event CtpFrontEventHandler^ OnCtpFrontEvent {
			void add(CtpFrontEventHandler^ handler) {
				CtpFront_delegate += handler;
			}
			void remove(CtpFrontEventHandler^ handler) {
				CtpFront_delegate -= handler;
			}
			void raise(Object^ sender, CtpFrontEventArgs^ e) {
				if (CtpFront_delegate)
					CtpFront_delegate(sender, e);
			}
		}

		/// <summary>
		/// 处理所有的OnErrRtn****回调事件
		/// </summary>
		event CtpErrRtnEventHandler^ OnCtpErrRtnEvent{
			void add(CtpErrRtnEventHandler^ handler) { CtpErrRtn_delegate += handler; }
			void remove(CtpErrRtnEventHandler^ handler) { CtpErrRtn_delegate -= handler; }
			void raise(Object^ sender, CtpErrRtnEventArgs^ args) {
				if (CtpErrRtn_delegate) CtpErrRtn_delegate(sender, args);
			}
		}

		/// <summary>
		/// 处理所有的OnRtn****回调事件
		/// </summary>
		event CtpRtnEventHandler^ OnCtpRtnEvent{
			void add(CtpRtnEventHandler^ handler) { CtpRtn_delegate += handler; }
			void remove(CtpRtnEventHandler^ handler) { CtpRtn_delegate -= handler; }
			void raise(Object^ sender, CtpRtnEventArgs^ e) {
				if (CtpRtn_delegate) CtpRtn_delegate(sender, e);
			}
		}

		/// <summary>
		/// 处理所有的OnRspQry****回调事件
		/// </summary>
		event CtpRspQryEventHandler^ OnCtpRspQryEvent{
			void add(CtpRspQryEventHandler^ handler) { CtpRspQry_delegate += handler; }
			void remove(CtpRspQryEventHandler^ handler) { CtpRspQry_delegate -= handler; }
			void raise(Object^ sender, CtpRspQryEventArgs^ e) {
				if (CtpRspQry_delegate) CtpRspQry_delegate(sender, e);
			}
		}

		/// <summary>
		/// 处理除了OnRspQry****之外，其他OnRsp****回调函数
		/// </summary>
		event CtpRspEventHandler^ OnCtpRspEvent{
			void add(CtpRspEventHandler^ handler) { CtpRsp_delegate += handler; }
			void remove(CtpRspEventHandler^ handler) { CtpRsp_delegate -= handler; }
			void raise(Object^ sender, CtpRspEventArgs^ e) {
				if (CtpRsp_delegate) CtpRsp_delegate(sender, e);
			}
		}

	public:
		/// <summary>
		///删除接口对象本身
		///@remark 不再使用本接口对象时,调用该函数删除接口对象
		/// </summary>
		void Release();

		/// <summary>
		///初始化
		///@remark 初始化运行环境,只有调用后,接口才开始工作
		/// </summary>
		void Init();

		/// <summary>
		///等待接口线程结束运行
		///@return 线程退出代码
		/// </summary>
		int Join();

		/// <summary>
		///获取当前交易日
		///@remark 只有登录成功后,才能得到正确的交易日
		/// </summary>
		/// <returns>获取到的交易日</returns>
		String^ GetTradingDay();

		/// <summary>
		///注册前置机网络地址
		///@param pszFrontAddress：前置机网络地址。
		///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
		///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
		/// </summary>
		void RegisterFront(String^ pszFrontAddress);


		///注册回调接口
		///@param pSpi 派生自回调接口类的实例
		/// void RegisterSpi(ThostFtdcTraderSpi^ pSpi);

		/// <summary>
		///订阅私有流。
		///@param nResumeType 私有流重传方式  
		///        THOST_TERT_RESTART:从本交易日开始重传
		///        THOST_TERT_RESUME:从上次收到的续传
		///        THOST_TERT_QUICK:只传送登录后私有流的内容
		///@remark 该方法要在Init方法前调用。若不调用则不会收到私有流的数据。
		/// </summary>
		void SubscribePrivateTopic(EnumTeResumeType nResumeType);

		/// <summary>
		///订阅公共流。
		///@param nResumeType 公共流重传方式  
		///        THOST_TERT_RESTART:从本交易日开始重传
		///        THOST_TERT_RESUME:从上次收到的续传
		///        THOST_TERT_QUICK:只传送登录后公共流的内容
		///@remark 该方法要在Init方法前调用。若不调用则不会收到公共流的数据。
		/// </summary>
		void SubscribePublicTopic(EnumTeResumeType nResumeType);

		/// <summary>
		///客户端认证请求
		/// </summary>
		int ReqAuthenticate(ThostFtdcReqAuthenticateField^ pReqAuthenticateField, int nRequestID);

		/// <summary>
		///用户登录请求
		/// </summary>
		int ReqUserLogin(ThostFtdcReqUserLoginField^ pReqUserLoginField, int nRequestID);

		/// <summary>
		///登出请求
		/// </summary>
		int ReqUserLogout(ThostFtdcUserLogoutField^ pUserLogout, int nRequestID);

		/// <summary>
		///用户口令更新请求
		/// </summary>
		int ReqUserPasswordUpdate(ThostFtdcUserPasswordUpdateField^ pUserPasswordUpdate, int nRequestID);

		/// <summary>
		///资金账户口令更新请求
		/// </summary>
		int ReqTradingAccountPasswordUpdate(ThostFtdcTradingAccountPasswordUpdateField^ pTradingAccountPasswordUpdate, int nRequestID);

		/// <summary>
		///报单录入请求
		/// </summary>
		int ReqOrderInsert(ThostFtdcInputOrderField^ pInputOrder, int nRequestID);

		/// <summary>
		///报单操作请求
		/// </summary>
		int ReqOrderAction(ThostFtdcInputOrderActionField^ pInputOrderAction, int nRequestID);

		/// <summary>
		///请求查询报单
		/// </summary>
		int ReqQryOrder(ThostFtdcQryOrderField^ pQryOrder, int nRequestID);

		/// <summary>
		///请求查询成交
		/// </summary>
		int ReqQryTrade(ThostFtdcQryTradeField^ pQryTrade, int nRequestID);

		/// <summary>
		///请求查询投资者持仓
		/// </summary>
		int ReqQryInvestorPosition(ThostFtdcQryInvestorPositionField^ pQryInvestorPosition, int nRequestID);

		/// <summary>
		///请求查询资金账户
		/// </summary>
		int ReqQryTradingAccount(ThostFtdcQryTradingAccountField^ pQryTradingAccount, int nRequestID);

		/// <summary>
		///请求查询投资者
		/// </summary>
		int ReqQryInvestor(ThostFtdcQryInvestorField^ pQryInvestor, int nRequestID);

		/// <summary>
		///请求查询交易编码
		/// </summary>
		int ReqQryTradingCode(ThostFtdcQryTradingCodeField^ pQryTradingCode, int nRequestID);

		/// <summary>
		///请求查询合约手续费率
		/// </summary>
		int ReqQryInstrumentCommissionRate(ThostFtdcQryInstrumentCommissionRateField^ pQryInstrumentCommissionRate, int nRequestID);

		/// <summary>
		///请求查询交易所
		/// </summary>
		int ReqQryExchange(ThostFtdcQryExchangeField^ pQryExchange, int nRequestID);

		/// <summary>
		///请求查询合约
		/// </summary>
		int ReqQryInstrument(ThostFtdcQryInstrumentField^ pQryInstrument, int nRequestID);

		/// <summary>
		///请求查询行情
		/// </summary>
		int ReqQryDepthMarketData(ThostFtdcQryDepthMarketDataField^ pQryDepthMarketData, int nRequestID);

		/// <summary>
		///请求查询投资者持仓明细
		/// </summary>
		int ReqQryInvestorPositionDetail(ThostFtdcQryInvestorPositionDetailField^ pQryInvestorPositionDetail, int nRequestID);

		/// <summary>
		///请求查询债券利息
		/// </summary>
		int ReqQryBondInterest(ThostFtdcQryBondInterestField^ pQryBondInterest, int nRequestID);

		/// <summary>
		///请求查询新股申购报单
		/// </summary>
		int ReqQrySubscribingSharesOrder(ThostFtdcQryOrderField^ pQryOrder, int nRequestID);

		/// <summary>
		///资金转出CTP请求请求
		/// </summary>
		int ReqFundOutCTPAccount(ThostFtdcReqFundIOCTPAccountField^ pReqFundIOCTPAccount, int nRequestID);

		/// <summary>
		///资金转入转出CTP查询请求
		/// </summary>
		int ReqQryFundIOCTPAccount(ThostFtdcQryFundIOCTPAccountField^ pQryFundIOCTPAccount, int nRequestID);

	};

}; // end of namespace