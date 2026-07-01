#include "TransporterView.h"

void TransporterView::DrawSelf()
{
	WorldView::DrawSelf();

	int index = -1;
	PrintLine("-Transporters-");
	for (const auto& transporter : model->transporters)
	{
		buffer << "Transporter (" << ++index << ")" << std::endl;
		auto position = transporter.GetPosition();
		buffer << "-Position: " << position.x << " " << position.y << std::endl;
		buffer << "-State: " << ToString(transporter.GetCurrentStatus()) << std::endl;
		const HaulJob job = transporter.GetJob();
		auto goods = goodsDatabase->TryGetElement(job.goodsId);
		std::string name = goods == nullptr ? "Unknown" : goods->name;
		buffer << "-Last/Current Job: " << "Delivering " << name << " x" << job.goodsCount << " from " << job.provider->GetName() << " to #" << job.requester->GetName() << std::endl;
		goods = goodsDatabase->TryGetElement(transporter.GetGoodsId());
		name = goods == nullptr ? "Unknown" : goods->name;
		buffer << "-Cargo: " << name << " x" << transporter.GetGoodsCount() << std::endl;
		buffer << "-Speed: " << transporter.GetSpeed() << std::endl;
		PrintLine("-------------------");
	}
}
