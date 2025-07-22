#ifndef ALARM_INTERNAL_ALARMMAPPER_H
#define ALARM_INTERNAL_ALARMMAPPER_H

#include <memory>

#include "../view/AlarmItemViewModel.h"
#include "AlarmEntity.h"

/**
 * Provides conversion between AlarmEntity and AlarmItemViewModel.
 *
 * This mapper is designed to be generic and robust against new attributes.
 * It uses explicit field mapping and, where possible, delegates to getter/setter methods.
 * When new attributes are added to either model, only this file needs to be updated.
 */
class AlarmMapper {
public:

    /**
     * Converts an AlarmEntity to an AlarmItemViewModel.
     * @param entity The backend alarm entity.
     * @return Unique pointer to the created AlarmItemViewModel.
     */
    static std::unique_ptr<AlarmItemViewModel> toViewModel(AlarmEntity const& entity) {
        auto viewModel = std::make_unique<AlarmItemViewModel>(entity.id);
        viewModel->setDisplayName(QString::fromStdString(entity.name));
        viewModel->setState(entity.isActive);
        viewModel->setDueTime(entity.dueTimeUtc);
        viewModel->setRepeated(entity.repeated);
        viewModel->setSnoozeTime(entity.snoozeTime);
        viewModel->setMaxSnoozeCount(entity.maxSnoozeCount);
        viewModel->setSnoozeCount(entity.snoozeCount);

        // @note: When adding new attributes to AlarmEntity or AlarmItemViewModel,
        // add the mapping here.

        return viewModel;
    }

    /**
     * Converts an AlarmItemViewModel to an AlarmEntity.
     * @param viewModel The frontend alarm view model.
     * @return The corresponding AlarmEntity.
     */
    static AlarmEntity toEntity(AlarmItemViewModel const& viewModel) {
        AlarmEntity entity {
            viewModel.getAlarmId(),
            viewModel.getDisplayName().toStdString(),
            viewModel.getState(),
            viewModel.getDueTime(),
            viewModel.isRepeated(),
            viewModel.snoozeTime(),
            viewModel.getMaxSnoozeCount(),
            viewModel.getSnoozeCount(),
        };

        // @note: When adding new attributes to AlarmEntity or AlarmItemViewModel,
        // add the mapping here.

        return entity;
    }
};

#endif