<?php
//dpm($content); // this will show all of the available fields for the unit/museum
//dpm($exhibition_content);
//dpm($imax_content);
//dpm($variables);
//dpm($variables);

$edit_link_text = '';
if(user_access('Administer EDAN museum records')) {
  $edit_link_text = l(t('Edit') . ' ' . $title,
    $edit_link,
    array('attributes' => array('title' => t('edit') . ' ' . $title)));
}
if(module_exists('devel') && isset($_GET['dpm-location']) && user_access('access devel information')){
  dpm($variables);
}
?>
<div class="edan-record--location">
  <div class="l-region--hero pane-page-header">
    <div class="l-container">
      <h1 class="page-title"><?php print $content['title']; ?></h1>
    </div>
  </div>


  <div class="layout l-container location-details">
      <div class="col col-sm-6 col-md-5 location-info-wrapper spacing-bottom">
        <?php if($img_uri): ?>
          <div class="field field--name-field-image field--type-image">
            <img src="<?php print $img_uri; ?>" />
          </div>
        <?php endif; ?>
        <div class="location-info">
          <?php if ($full_address): ?>
            <div class="location-address spacing-half">
              <?php print $full_address;?>
              <?php if(isset($content['geolocation']['extended']['url'])) : ?>
                <p>
                  <a href="<?php print $content['geolocation']['extended']['url'];?>" target="_blank" class="map-link block-display">
                    <?php print $content['geolocation']['extended']['url_text'] ? $content['geolocation']['extended']['url_text'] : '' ?>
                    <span class="fa fa-map-marker" aria-hidden="true"></span>
                  </a>
                </p>
              <?php endif; ?>
              <?php if(isset($location_link)): ?>
                <p><?php print $location_link; ?></p>
              <?php endif; ?>
            </div>
          <?php endif; ?>
          <?php if (isset($floorplan)): ?>
            <div class="spacing-half"><?php  print $floorplan; ?></div>
          <?php endif; ?>
          <?php if (isset($content['hours'])): ?>
            <div class="location-hours spacing-half">
              <?php print $content['hours']; ?></div>
          <?php endif; ?>
          <?php if (isset($content['admission'])): ?>
            <div class="location-admission">
              <?php print $content['admission']; ?></div>
          <?php endif; ?>
        </div>

      </div>

      <div class="col <?php print $img_uri ? 'col col-sm-6 col-md-7 last' : ''; ?>">
        <?php if ($edit_link_text): ?>
          <div class="edit-link"><?php print $edit_link_text;?></div>
        <?php endif; ?>
        <div class="location-desc">
          <?php if (!empty($content['description'])): ?>
            <div class="info spacing-bottom">
              <h2><?php print t('About'); ?></h2>
              <?php print $content['description']; ?>
            </div>
          <?php endif; ?>

            <?php if (!empty($content['highlights'])): ?>
              <div class="info spacing-bottom">
                <h2><?php print t('Highlights'); ?></h2>
                  <?php print $content['highlights']; ?>
              </div>
            <?php endif; ?>

          </div>


        <?php if(!empty($accordion)):
          print theme('si_field_collection_accordion', $accordion);
        endif; ?>
      </div>
  </div>
  <?php if(!empty($tabs)):
    ?>
    <div class="wrapper--sitabs">

        <?php print theme('si_field_collection_tabs', $tabs); ?>

    </div>

  <?php endif; ?>
  </div>